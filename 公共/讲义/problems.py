"""每环 5 道题：从 环NN_xxx/题N_*.c 的文件头读题目，从 答案/题N.c 读参考代码，
从 公共/讲义/程序/环NN.txt 读 main 和输入，拼成能直接编译运行的完整程序。

程序/环NN.txt 的格式：
  == 题N
  -- 前置            放在 #include 后面、答案函数前面（结构体定义等）
  -- main            main 和它要用的辅助函数
  -- 输入            运行时从键盘输入的内容（可省）
  -- 文件 名字       运行前先准备好的文件（可省）
  -- 显示文件 名字   运行后把这个文件的内容也显示出来（可省）
运行结果由 check_progs.py 编译运行后写进 程序/输出.json，生成讲义时直接读。
"""
import glob, json, os, re

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
PROG_DIR = os.path.join(HERE, '程序')
OUT_JSON = os.path.join(PROG_DIR, '输出.json')


def width(s):
    return sum(2 if ord(c) > 0x2E80 else 1 for c in s)


# ── 题目文件头 ──────────────────────────────────────────
def read_header(path):
    """返回 dict：tag、title、stem（题目原文行）、req（要求行）、hints、refs、limit"""
    text = open(path, encoding='utf-8').read()
    m = re.match(r'\s*/\*(.*?)\*/', text, re.S)
    raw = [re.sub(r'^ ?\* ?', '', l) for l in m.group(1).split('\n')]
    raw = [l.rstrip() for l in raw]
    while raw and not raw[0].strip():
        raw.pop(0)
    first = raw.pop(0)                                   # 环06 题1【代表题】2022 第4题
    fm = re.match(r'环\d+ 题\d+\s*(【[^】]*】)?\s*(.*)', first)
    tag = (fm.group(1) or '').strip('【】')
    source = fm.group(2).strip()
    name = re.sub(r'^题\d+_', '', os.path.splitext(os.path.basename(path))[0])

    groups = []                                          # [label, indent, [lines]]
    blank = False
    for l in raw:
        if not l.strip():
            blank = True
            continue
        lm = re.match(r'^([^\s：][^：]{0,11})：(.*)$', l)
        if lm and not l.startswith(' '):
            label, rest = lm.group(1), lm.group(2)
            if label.startswith('你要写') and label != '你要写':     # 「你要写两个函数：」
                rest, label = '写' + label[3:] + '：' + rest, '你要写'
            groups.append([label, width(lm.group(1)) + 2, [rest] if rest else []])
        elif l.startswith(' ') and groups:
            g = groups[-1]
            cut = 0
            while cut < len(l) and cut < g[1] and l[cut] == ' ':
                cut += 1
            if blank and g[2]:
                g[2].append('')
            g[2].append(l[cut:])
        else:
            prev = groups[-1] if groups else None
            label = '你要写' if prev and prev[0] == '你要写' and not blank else '备注'
            if l.startswith('你要写'):
                l, label = '写' + l[3:], '你要写'
            groups.append([label, 0, [l]])
        blank = False
    groups = [g for g in groups if g]

    stem, req, hints, refs, limit = [], [], [], [], ''
    for label, _, lines in groups:
        kept = []
        for ln in lines:
            if ln == '':
                if kept and kept[-1] != '':
                    kept.append('')
                continue
            if not ln.startswith(' ') and not re.match(r'^[*\s]+$', ln):
                parts = re.split(r'(?<=。)', ln)
                out = []
                for p in parts:
                    if not p.strip():
                        continue
                    rm = re.search(r'卡住先看：(.*)', p)
                    if rm:
                        refs.append(rm.group(1).strip('。 '))
                        p = p[:rm.start()]
                    lm2 = re.search(r'限时\s*(\d+)\s*分钟', p)
                    if lm2:
                        limit = lm2.group(1)
                        p = re.sub(r'(这题综合性强，)?限时\s*\d+\s*分钟。?', '', p)
                    if not re.match(r'(真题|原题|题目)', label) and (
                            '测试' in p or '写完运行' in p or re.search(r'考试(时还要写|要写完整程序|时 main 里)', p)
                            or re.search(r'在 \w+\.h 里', p)):
                        continue
                    p = re.sub(r'（[^（）]*这里不测）', '', p)
                    out.append(p)
                ln = ''.join(out).rstrip()
                if not ln.strip():
                    continue
            kept.append(ln)
        if not kept:
            continue
        if re.match(r'(真题|原题|题目)', label):
            stem += kept
        elif label in ('你要写', '备注'):
            if req and kept and req[-1] != '':
                req.append('')
            req += kept
        elif label == '卡住先看':
            refs.append(' '.join(kept).strip('。 '))
        elif label.startswith('说明') and stem:
            stem += [''] + ['说明：' + kept[0]] + kept[1:]
        else:
            hints.append((label, kept))
    refs = [r.replace('基础.c', '讲义') for r in refs]
    while req and req[-1] == '':
        req.pop()
    return {'tag': tag, 'source': source, 'name': name, 'stem': stem, 'req': req,
            'hints': hints, 'refs': refs, 'limit': limit}


# ── 参考答案 ──────────────────────────────────────────
def read_answer(path):
    """返回 (要点, 代码)。去掉开头那行注释和 #include。"""
    text = open(path, encoding='utf-8').read()
    m = re.match(r'\s*/\*(.*?)\*/\s*', text, re.S)
    tip = ''
    if m:
        c = ' '.join(m.group(1).split())
        c = re.sub(r'^题\d+\s*答案\s*(（[^）]*）)?。?\s*', '', c)     # 「题1 答案（冒泡）。」
        tip = re.sub(r'^卡点：', '', c)
        text = text[m.end():]
    code = '\n'.join(l for l in text.split('\n') if not l.startswith('#include'))
    return tip.strip(), code.strip('\n')


# ── 程序/环NN.txt ─────────────────────────────────────
def read_specs(nn):
    path = os.path.join(PROG_DIR, '环%s.txt' % nn)
    specs, cur, sec = {}, None, None
    for l in open(path, encoding='utf-8').read().split('\n'):
        if l.startswith('== 题'):
            cur = {'pre': [], 'main': [], 'input': [], 'files': {}, 'show': []}
            specs[int(l[4:].strip())] = cur
            sec = None
            continue
        if l.startswith('-- '):
            name, _, arg = l[3:].strip().partition(' ')
            if name == '文件':
                cur['files'][arg] = []
                sec = ('file', arg)
            elif name == '显示文件':
                cur['show'].append(arg)
                sec = None
            else:
                sec = {'前置': 'pre', 'main': 'main', '输入': 'input'}[name]
            continue
        if cur is None or sec is None:
            continue
        if isinstance(sec, tuple):
            cur['files'][sec[1]].append(l)
        else:
            cur[sec].append(l)
    for s in specs.values():
        for k in ('pre', 'main', 'input'):
            while s[k] and not s[k][-1].strip():
                s[k].pop()
        for f in s['files']:
            while s['files'][f] and not s['files'][f][-1].strip():
                s['files'][f].pop()
    return specs


def full_program(answer_code, spec):
    body = '\n'.join(spec['pre']) + '\n' + answer_code + '\n' + '\n'.join(spec['main'])
    inc = ['<stdio.h>']
    if re.search(r'\b(strlen|strcmp|strcpy|strcat|strcspn)\b', body):
        inc.append('<string.h>')
    if re.search(r'\b(fabs|sqrt|pow)\b', body):
        inc.append('<math.h>')
    if re.search(r'\b(malloc|free)\b', body):
        inc.append('<stdlib.h>')
    parts = ['\n'.join('#include ' + i for i in inc)]
    if spec['pre']:
        parts.append('\n'.join(spec['pre']))
    parts.append(answer_code)
    parts.append('\n'.join(spec['main']))
    return '\n\n'.join(parts) + '\n'


def ring_folder(nn):
    return [d for d in glob.glob(os.path.join(ROOT, '环%s_*' % nn)) if os.path.isdir(d)][0]


def ring_problems(nn):
    """[(n, header, tip, program, spec)]，n = 1..5"""
    folder = ring_folder(nn)
    specs = read_specs(nn)
    out = []
    for n in range(1, 6):
        qf = glob.glob(os.path.join(folder, '题%d_*.c' % n))[0]
        hd = read_header(qf)
        tip, code = read_answer(os.path.join(folder, '答案', '题%d.c' % n))
        out.append((n, hd, tip, full_program(code, specs[n]), specs[n]))
    return out


def load_outputs():
    if os.path.exists(OUT_JSON):
        return json.load(open(OUT_JSON, encoding='utf-8'))
    return {}
