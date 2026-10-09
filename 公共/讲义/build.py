#!/usr/bin/env python3
"""把 公共/讲义/环NN.txt 生成为 环NN_xxx/讲义.html，把 目录.txt 生成为 讲义目录.html。

用法：  python3 公共/讲义/build.py            生成仓库里的文件
        python3 公共/讲义/build.py --site DIR 生成一套用 index.html / r01.html 互链的网页（发布用：index.html 是主页，r01–r13 作附属文件）

源文件格式（一行一个指令，空行分段）：
  @title / @intro / @kicker        页头
  == recall … ==                   「开始之前」回顾块，里面每行  问题 => 答案 @ 出处
  # 锚点 | 标题 | 说明              一大部分
  ## 锚点 | 目录短名 | 编号 | 标题  一节（编号、标题可空）
  ::code / ::calc / ::exam / ::pair 左 | 右 / ::table / ::fix / ::note … ::   块
  - 开头是列表；> 开头是灰色小字；其余是段落
行内：`代码`  **加粗**  {{空}}  ~~坑~~  «输出»
"""
import html, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))          # c-study/

RINGS = [
    ("01", "环01_级数", "级数与数学模拟"),
    ("02", "环02_数位", "数位处理"),
    ("03", "环03_素数因子", "素数与因子"),
    ("04", "环04_枚举", "枚举与组合"),
    ("05", "环05_图案", "图案输出"),
    ("06", "环06_排序查找", "排序·查找·插入·合并"),
    ("07", "环07_矩阵", "矩阵操作"),
    ("08", "环08_字符串", "字符串处理"),
    ("09", "环09_函数指针参数", "函数与指针参数"),
    ("10", "环10_递归", "递归"),
    ("11", "环11_指针数组字符串", "用指针处理数组和字符串"),
    ("12", "环12_结构体", "结构体与链表"),
    ("13", "环13_文件", "文件"),
]

FONTS = ('<link rel="preconnect" href="https://fonts.googleapis.com">\n'
         '<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>\n'
         '<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;600'
         '&family=Noto+Sans+SC:wght@300;400;500;700&family=Atkinson+Hyperlegible+Next:wght@300;400;500;700&display=swap">\n')

LEGEND = """      <details class="legend">
        <summary>灰色小字的出处是什么意思</summary>
        <dl>
          <dt>A-2012-1</dt><dd>学长回忆的川师考研真题，2012 年第 1 题</dd>
          <dt>真选43·川大2017</dt><dd>圣才题库里的考研真题精选，别的学校的真题</dd>
          <dt>川师卷2019-20 一-8</dt><dd>川师本科期末卷，2019-20 学年，第一大题第 8 题</dd>
          <dt>配-2-72</dt><dd>圣才《第五版配套题库》第 2 章第 72 题，Notion「教材题库」里同名</dd>
          <dt>教材3.4</dt><dd>谭浩强《C程序设计》第五版 3.4 节</dd>
          <dt>环01 ①</dt><dd>这套讲义里的环和节，回顾时用</dd>
        </dl>
      </details>
"""


def die(msg):
    sys.exit("讲义生成失败：" + msg)


# ── 行内 ──────────────────────────────────────────────
def inline(s):
    codes = []

    def keep(m):
        codes.append('<code>' + html.escape(m.group(1), quote=False) + '</code>')
        return '\x00%d\x00' % (len(codes) - 1)

    s = re.sub(r'`([^`]+)`', keep, s)
    s = html.escape(s, quote=False)
    s = re.sub(r'«(.+?)»', r'<span class="out">\1</span>', s)
    s = re.sub(r'\{\{(.+?)\}\}', r'<span class="a" tabindex="0">\1</span>', s)
    s = re.sub(r'~~(.+?)~~', r'<span class="trap">\1</span>', s)
    s = re.sub(r'\*\*(.+?)\*\*', r'<b>\1</b>', s)
    if '{{' in s or '}}' in s or '~~' in s or '**' in s or '`' in s:
        die('行内标记没配对：' + s[:80])
    return re.sub(r'\x00(\d+)\x00', lambda m: codes[int(m.group(1))], s)


def code_block(lines):
    body = html.escape('\n'.join(lines), quote=False)
    return '<div class="code"><pre><code class="c">' + body + '</code></pre></div>'


def calc_block(lines):
    out = ['<div class="calc">']
    for ln in lines:
        p = [x.strip() for x in ln.split('‖')]
        if len(p) < 3:
            die('calc 行要用 ‖ 分成 写法‖箭头‖答案[‖说明]：' + ln)
        left, arrow, ans = p[0], p[1], p[2]
        note = p[3] if len(p) > 3 else ''
        if '`' in left or re.search(r'[\u4e00-\u9fff]', left):
            lh = '<span>' + inline(left) + '</span>'          # 一句话，不是代码
        else:
            lh = '<code>' + html.escape(left, quote=False) + '</code>'
        ah = '<span class="a" tabindex="0">' + inline(ans) + '</span>' if ans else ''
        nh = ' <span class="note">' + inline(note) + '</span>' if note else ''
        out.append('  %s<span class="arrow">%s</span><span>%s%s</span>' % (lh, html.escape(arrow), ah, nh))
    out.append('</div>')
    return '\n'.join(out)


def exam_line(ln):
    src = ''
    if ' @ ' in ln:
        ln, src = ln.rsplit(' @ ', 1)
    if ' => ' in ln:
        q, a = ln.split(' => ', 1)
        body = inline(q) + ' → <span class="a" tabindex="0">' + inline(a) + '</span>'
    else:
        body = inline(ln)
    if src:
        body += '<span class="src">' + html.escape(src.strip()) + '</span>'
    return '<p class="q">' + body + '</p>'


def exam_block(lines, title='真题里这样考'):
    return '<div class="exam">\n<p>' + title + '</p>\n' + '\n'.join(exam_line(l) for l in lines) + '\n</div>'


def pair_block(head, lines):
    labs = [x.strip() for x in head.split('|')]
    if len(labs) != 2 or '---' not in lines:
        die('pair 需要「左 | 右」和一行 ---')
    k = lines.index('---')
    parts = []
    for lab, body in zip(labs, (lines[:k], lines[k + 1:])):
        parts.append('<div><div class="lab">' + inline(lab) + '</div>' + code_block(body) + '</div>')
    return '<div class="pair">' + ''.join(parts) + '</div>'


def table_block(lines):
    rows = [[c.strip() for c in re.split(r'(?<!\|)\|(?!\|)', l)] for l in lines]   # 单个 | 分列，|| 不算
    h = '<div class="tbl"><table>\n<tr>' + ''.join('<th>' + inline(c) + '</th>' for c in rows[0]) + '</tr>\n'
    for r in rows[1:]:
        h += '<tr>' + ''.join('<td>' + inline(c) + '</td>' for c in r) + '</tr>\n'
    return h + '</table></div>'


# ── 正文 ──────────────────────────────────────────────
def render_body(lines, ring=None):
    """返回 (recall_html, body_html, sections)"""
    out, recall, secs = [], '', []
    para, items = [], []
    open_sec = False
    i = 0

    def flush():
        nonlocal para, items
        if para:
            text = ' '.join(para)
            if text.startswith('> '):
                out.append('<p class="mute small">' + inline(text[2:]) + '</p>')
            else:
                out.append('<p>' + inline(text) + '</p>')
            para = []
        if items:
            out.append('<ul>' + ''.join('<li>' + inline(t) + '</li>' for t in items) + '</ul>')
            items = []

    while i < len(lines):
        ln = lines[i].rstrip()
        i += 1
        if ln.startswith('%'):                     # 注释行
            continue
        if ln == '== recall':
            j = lines.index('==', i)
            rl = [l.strip() for l in lines[i:j] if l.strip()]
            recall = ('<section class="recall" id="recall">\n<h2>开始之前，先回想一下</h2>\n'
                      '<p>这些是前面学过、这一环又要用到的基础。想不起来就回到出处那一节再看一眼。</p>\n'
                      + '\n'.join(exam_line(l) for l in rl) + '\n</section>')
            i = j + 1
            continue
        if ln.startswith('::'):
            flush()
            kind, _, head = ln[2:].partition(' ')
            j = i
            while lines[j].rstrip() != '::':
                j += 1
            blk = [l.rstrip('\n') for l in lines[i:j]]
            i = j + 1
            if kind == 'code':
                out.append(code_block(blk))
            elif kind == 'out':                     # 程序输出，原样显示
                out.append('<div class="code"><pre class="o">' + html.escape('\n'.join(blk), quote=False) + '</pre></div>')
            elif kind == 'outa':                    # 程序输出，默认盖住
                out.append('<div class="code oa" tabindex="0"><pre class="o">' + html.escape('\n'.join(blk), quote=False)
                           + '</pre></div>')
            elif kind == 'calc':
                out.append(calc_block([l for l in blk if l.strip()]))
            elif kind == 'exam':
                out.append(exam_block([l.strip() for l in blk if l.strip()], head or '真题里这样考'))
            elif kind == 'pair':
                out.append(pair_block(head, blk))
            elif kind == 'table':
                out.append(table_block([l for l in blk if l.strip()]))
            elif kind == 'fix':
                out.append('<p class="fix">' + inline(' '.join(l.strip() for l in blk)) + '</p>')
            elif kind == 'note':
                out.append('<p class="mute small">' + inline(' '.join(l.strip() for l in blk)) + '</p>')
            else:
                die('不认识的块 ::' + kind)
            continue
        if ln.startswith('## '):
            flush()
            if open_sec:
                out.append('</section>')
            p = [x.strip() for x in ln[3:].split('|')]
            sid, short, no, title = (p + ['', '', '', ''])[:4]
            secs.append((sid, short))
            out.append('<section class="sec" id="%s" data-short="%s">' % (sid, html.escape(short)))
            if title:
                noh = '<span class="no">%s</span>' % html.escape(no) if no else ''
                out.append('<h3>%s<span class="t">%s</span></h3>' % (noh, inline(title)))
            open_sec = True
            continue
        if ln.startswith('# '):
            flush()
            if open_sec:
                out.append('</section>')
                open_sec = False
            p = [x.strip() for x in ln[2:].split('|')]
            pid, title, desc = (p + ['', '', ''])[:3]
            secs.append(('#' + pid, title))
            out.append('<div class="part" id="%s">\n<h2>%s</h2>%s\n</div>'
                       % (pid, inline(title), '\n<p>' + inline(desc) + '</p>' if desc else ''))
            continue
        if not ln.strip():
            flush()
            continue
        if ln.startswith('- '):
            if para:
                flush()
            items.append(ln[2:].strip())
            continue
        if items and ln.startswith('  '):
            items[-1] += ' ' + ln.strip()
            continue
        para.append(ln.strip())
    flush()
    if open_sec:
        out.append('</section>')
    return recall, '\n'.join(out), secs


def read_src(path):
    meta, body = {}, []
    with open(path, encoding='utf-8') as f:
        lines = f.read().split('\n')
    k = 0
    while k < len(lines) and (lines[k].startswith('@') or not lines[k].strip()):
        if lines[k].startswith('@'):
            key, _, val = lines[k][1:].partition(' ')
            meta[key] = val.strip()
        k += 1
    return meta, lines[k:]


def page(title, desc, main, toc_secs, mode, attrs=''):
    css = open(os.path.join(HERE, 'style.css'), encoding='utf-8').read()
    js = open(os.path.join(HERE, 'script.js'), encoding='utf-8').read()
    toc_json = ''
    head = ''
    if mode in ('repo', 'site-sub'):
        head = ('<!doctype html>\n<html lang="zh-CN">\n<meta charset="utf-8">\n'
                '<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">\n'
                '<!-- 这个文件由 公共/讲义/build.py 生成，要改内容请改 公共/讲义 里的源文件。 -->\n')
    return (head + '<title>' + html.escape(title) + '</title>\n'
            '<meta name="description" content="' + html.escape(desc) + '">\n' + FONTS +
            '<style>\n' + css + '</style>\n\n<div id="progress" aria-hidden="true"></div>\n'
            '<div class="wrap hide" id="root"' + attrs + '>\n'
            '  <nav class="toc" id="toc" aria-label="目录"></nav>\n  <main>\n' + main +
            '\n  </main>\n</div>\n'
            '<div class="fab" id="fab"><button type="button" class="m" id="fab-toc" aria-label="打开目录">目录</button>'
            '<button type="button" id="fab-top" aria-label="回到顶部">↑</button></div>\n'
            '<div class="drawer" id="drawer"><div class="shade"></div><div class="panel"><nav class="toc" id="toc-d" aria-label="目录"></nav></div></div>\n'
            '\n<script>\n' + js + '</script>\n')


def link_ring(nn, mode, here_is_index=False):
    folder = dict((r[0], r[1]) for r in RINGS)[nn]
    if mode == 'site':
        return 'r%s.html' % nn
    return (folder if here_is_index else '../' + folder) + '/讲义.html'


def link_index(mode):
    return 'index.html' if mode == 'site' else '../讲义目录.html'


# ── 每环 5 道题（题目、要求、完整程序、运行结果）──────────────
CJK = re.compile(r'[\u3000-\u9fff\uff00-\uffef]')
CIRC = '①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳'


def is_fig(ln):
    """图案、代码、例子这类要原样排的行"""
    return bool(ln.strip()) and (not CJK.search(ln) or re.search(r'\S {3,}\S', ln))


def ptext(s):
    s = html.escape(s.replace('/ ***found*** /', '/***found***/'), quote=False)
    return re.sub(r'(?<![\w.])([A-Za-z_]\w*\([^()（）\u4e00-\u9fff]*\))', r'<code>\1</code>', s)


def text_blocks(lines):
    out, para, fig = [], [], []

    def flush_para():
        if para:
            out.append('<p>' + ptext(''.join(para)) + '</p>')
            para.clear()

    def flush_fig():
        if fig:
            out.append('<pre class="fig">' + html.escape('\n'.join(fig).replace('/ ***found*** /', '/***found***/'), quote=False) + '</pre>')
            fig.clear()

    for ln in lines:
        if not ln.strip():
            flush_para(); flush_fig()
            continue
        if is_fig(ln):
            flush_para()
            fig.append(ln)
            continue
        flush_fig()
        t = ln.strip()
        if para and (ln.startswith(' ') or re.match(r'（\d）|[^\s：]{1,8}：', t) or re.search(r'[。：！？」）]$', para[-1])):
            flush_para()
        if para and re.search(r'[A-Za-z0-9]$', para[-1]) and re.match(r'[A-Za-z0-9]', t):
            t = ' ' + t
        para.append(t)
    flush_para(); flush_fig()
    return '\n'.join(out)


def ref_links(refs, nn, mode, ids):
    """「讲义 第①③节、细10」「环07 讲义第③节」→ 链接"""
    out = []
    for r in refs:
        for part in re.split(r'[、，]', r):
            rm = re.match(r'\s*环(\d\d)', part)
            ring = rm.group(1) if rm else nn
            for m in re.finditer(r'([①-⑳])|细(\d+)', part):
                sid = ('s%d' % (CIRC.index(m.group(1)) + 1)) if m.group(1) else 'd' + m.group(2)
                text = m.group(1) or '细' + m.group(2)
                if ring == nn:
                    if sid in ids:
                        out.append('<a href="#%s">%s</a>' % (sid, text))
                else:
                    out.append('<a href="%s#%s">环%s %s</a>' % (link_ring(ring, mode), sid, ring, text))
    return ' '.join(out)


def problems_part(nn, mode, ids):
    sys.dont_write_bytecode = True
    sys.path.insert(0, HERE)
    import problems
    outs = problems.load_outputs()
    secs = [('#zt', '5 道真题')]
    h = ['<div class="part" id="zt">\n<h2>5 道真题</h2>\n<p>先自己写，写完再打开完整程序对照。每个程序都编译运行过，下面的运行结果就是它的真实输出。</p>\n</div>']
    for n, hd, tip, program, spec in problems.ring_problems(nn):
        title = re.sub(r'(?<=[A-Za-z0-9])(?=[\u4e00-\u9fff])|(?<=[\u4e00-\u9fff])(?=[A-Za-z0-9])', ' ', hd['name'])
        sid = 't%d' % n
        secs.append((sid, '题%d %s' % (n, title)))
        meta = []
        if hd['tag']:
            meta.append('<span class="ptag">%s</span>' % html.escape(hd['tag']))
        if hd['source']:
            meta.append(html.escape(hd['source']))
        if hd['limit']:
            meta.append('限时 %s 分钟' % hd['limit'])
        req = [l.replace('写在下面', '写出来') for l in hd['req']]
        res = outs.get('%s-%d' % (nn, n))
        io = []
        if spec['input']:
            io.append('<div class="io"><p class="lab">输入</p><pre>%s</pre></div>' % html.escape('\n'.join(spec['input']), quote=False))
        for fname, flines in spec['files'].items():
            io.append('<div class="io"><p class="lab">文件 %s 原有内容</p><pre>%s</pre></div>' % (html.escape(fname), html.escape('\n'.join(flines), quote=False)))
        if res:
            o = res['out'].rstrip('\n').split('\n')
            if len(o) > 14:
                o = o[:8] + ['⋯（共 %d 行，中间省略）' % len(o)] + o[-3:]
            if res['out'].strip():
                io.append('<div class="io"><p class="lab">运行结果</p><pre>%s</pre></div>' % html.escape('\n'.join(o), quote=False))
            for fname, content in res['files'].items():
                io.append('<div class="io"><p class="lab">运行后文件 %s 的内容</p><pre>%s</pre></div>' % (html.escape(fname), html.escape(content.rstrip('\n'), quote=False)))
        hints = ''.join('<li><b>%s</b>%s</li>' % (html.escape(lab), ptext(''.join(x.strip() for x in ls))) for lab, ls in hd['hints'])
        refs = ref_links(hd['refs'], nn, mode, ids)
        h.append(
            '<section class="sec prob" id="%s" data-short="%s">\n<h3><span class="no">题%d</span><span class="t">%s</span></h3>\n'
            '<p class="pmeta">%s</p>\n<div class="stem">%s</div>\n%s%s%s'
            '<div class="prog"><button class="prog-btn" type="button" aria-expanded="false">完整程序</button>\n<div class="prog-body">\n'
            '%s<div class="code" data-label="完整程序"><pre><code class="c">%s</code></pre></div>\n%s\n</div></div>\n</section>'
            % (sid, html.escape('题%d %s' % (n, title)), n, html.escape(title), ' · '.join(meta), text_blocks(hd['stem']),
               ('<div class="req"><p class="lab">要求</p>%s</div>\n' % text_blocks(req)) if req else '',
               ('<ul class="hints">%s</ul>\n' % hints) if hints else '',
               ('<p class="refs">对应讲义　%s</p>\n' % refs) if refs else '',
               ('<p class="tip"><b>易错</b>%s</p>\n' % ptext(tip)) if tip else '',
               html.escape(program.rstrip('\n'), quote=False), '\n'.join(io)))
    return '\n'.join(h), secs


def build_ring(nn, folder, name, mode, outdir):
    src = os.path.join(HERE, '环%s.txt' % nn)
    if not os.path.exists(src):
        return None
    meta, lines = read_src(src)
    recall, body, secs = render_body(lines, nn)
    idx = [r[0] for r in RINGS].index(nn)
    prev_l = ('<a href="%s"><small>← 上一环</small>环%s %s</a>' % (link_ring(RINGS[idx - 1][0], mode), RINGS[idx - 1][0], RINGS[idx - 1][2])
              if idx > 0 else '<span></span>')
    next_l = ('<a href="%s"><small>下一环 →</small>环%s %s</a>' % (link_ring(RINGS[idx + 1][0], mode), RINGS[idx + 1][0], RINGS[idx + 1][2])
              if idx + 1 < len(RINGS) else '<span></span>')
    ids = set(re.findall(r'<section class="sec" id="([^"]+)"', body))
    probs, psecs = problems_part(nn, mode, ids)
    secs = psecs + secs
    main = ('    <header>\n      <p class="kicker"><a href="%s">C 语言讲义</a><span class="chip">环 %s</span></p>\n'
            '      <h1>%s</h1>\n      <div class="intro">\n%s      </div>\n'
            '      <div class="tools">\n        <button class="btn" id="toggle" type="button" aria-pressed="false">全部揭开</button>\n      </div>\n'
            '      <div class="resume" id="resume"></div>\n'
            '      <details class="toc-m"><summary>目录</summary><nav class="toc" id="toc-m" aria-label="目录"></nav></details>\n'
            '    </header>\n' % (link_index(mode), nn, html.escape(meta.get('title', name)),
                                ''.join('        <p>' + inline(p) + '</p>\n' for p in meta.get('intro', '').split(' // ')[:1] if p)))
    main += probs + '\n' + recall + '\n' + body
    main += ('\n    <div class="end">\n      <nav class="ringnav">%s<a href="%s"><small>目录</small>全部 13 环</a>%s</nav>\n    </div>\n'
             % (prev_l, link_index(mode), next_l))
    title = '环%s %s讲义' % (nn, meta.get('short', name))
    tone = tone_of(nn)
    attrs = ' data-ring="%s" data-name="%s" data-home="%s" data-tone="%s"' % (nn, html.escape(meta.get('short', name)), link_index(mode), tone)
    html_s = page(title, meta.get('desc', 'C 语言环%s：%s' % (nn, name)), main, secs,
                  'site-sub' if mode == 'site' else mode, attrs)    # 网页版的环页面是附属文件，要自带 doctype
    out = os.path.join(outdir, 'r%s.html' % nn) if mode == 'site' else os.path.join(ROOT, folder, '讲义.html')
    with open(out, 'w', encoding='utf-8') as f:
        f.write(html_s)
    return out


def tone_of(nn):
    # 七种布色轮换：石板蓝、赭黄、鼠尾草、灰粉、青绿、薰衣草、暖灰（颜色定义在 style.css）
    return 'abcdefg'[(int(nn) - 1) % 7]


def build_index(mode, outdir):
    meta, lines = read_src(os.path.join(HERE, '目录.txt'))
    recall, body, secs = render_body(lines)
    li = []
    for nn, folder, name in RINGS:
        m, _ = read_src(os.path.join(HERE, '环%s.txt' % nn)) if os.path.exists(os.path.join(HERE, '环%s.txt' % nn)) else ({}, [])
        li.append('<li data-ring="%s" data-tone="%s"><span class="rn">%s</span><a href="%s">%s</a><p>%s</p></li>'
                  % (nn, tone_of(nn), nn, link_ring(nn, mode, True) if mode == 'repo' else link_ring(nn, mode), html.escape(name),
                     inline(m.get('summary', ''))))
    body = body.replace('<p>@@RINGS@@</p>', '<ol class="rings">' + ''.join(li) + '</ol>')
    main = ('    <header>\n      <p class="kicker">四川师大 0854 · 专业课 C 语言</p>\n      <h1>%s</h1>\n'
            '      <div class="intro">\n%s      </div>\n'
            '      <details class="toc-m"><summary>目录</summary><nav class="toc" id="toc-m" aria-label="目录"></nav></details>\n'
            '    </header>\n' % (html.escape(meta['title']),
                                ''.join('        <p>' + inline(p) + '</p>\n' for p in meta.get('intro', '').split(' // '))))
    main += body + '\n    <div class="end">\n' + LEGEND + '    </div>\n'
    html_s = page(meta['title'], meta.get('desc', ''), main, secs, mode)
    html_s = html_s.replace('<div class="wrap hide" id="root">', '<div class="wrap hide index" id="root" data-tone="a">')
    out = os.path.join(outdir, 'index.html') if mode == 'site' else os.path.join(ROOT, '讲义目录.html')
    if mode == 'repo':
        html_s = html_s.replace('href="../', 'href="')
    with open(out, 'w', encoding='utf-8') as f:
        f.write(html_s)
    return out


if __name__ == '__main__':
    mode, outdir = 'repo', ROOT
    if len(sys.argv) > 2 and sys.argv[1] == '--site':
        mode, outdir = 'site', sys.argv[2]
        os.makedirs(outdir, exist_ok=True)
    made = [build_ring(nn, folder, name, mode, outdir) for nn, folder, name in RINGS]
    made.append(build_index(mode, outdir))

    for m in made:
        if m:
            print('生成', os.path.relpath(m, outdir))
    # 顺手检查「看第几节」的引用有没有指错
    import subprocess
    sys.exit(subprocess.call([sys.executable, os.path.join(HERE, 'check_refs.py')]))
