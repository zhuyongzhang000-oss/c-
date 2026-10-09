#!/usr/bin/env python3
"""检查讲义、题文件、自测里「看第几节」的引用都指向真实存在的节。用法：python3 公共/讲义/check_refs.py"""
import glob, os, re, sys
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
CIRC = '①②③④⑤⑥⑦⑧⑨'
secs = {}
for p in sorted(glob.glob(os.path.join(HERE, '环*.txt'))):
    nn = re.search(r'环(\d\d)', p).group(1)
    s = set()
    for ln in open(p, encoding='utf-8'):
        if ln.startswith('## '):
            f = [x.strip() for x in ln[3:].split('|')]
            if len(f) > 2 and f[2]:
                s.add(f[2])
    secs[nn] = s
bad = []
nchk = [0]
def chk(where, nn, sec):
    nchk[0] += 1
    if nn not in secs:
        bad.append('%s：没有环%s' % (where, nn)); return
    if sec not in secs[nn]:
        bad.append('%s：环%s 没有「%s」' % (where, nn, sec))
def expand(token):
    """'①③④' → ['①','③','④']；'细3–细5' → 细3..细5；'细3' → ['细3']"""
    m = re.fullmatch(r'细(\d+)[–-]细(\d+)', token)
    if m: return ['细%d' % i for i in range(int(m.group(1)), int(m.group(2)) + 1)]
    if token.startswith('细'): return [token]
    return [c for c in token if c in CIRC]
ref = re.compile(r'环(\d\d)\s*(?:讲义)?\s*(?:第)?((?:细\d+(?:[–-]细\d+)?)|[①-⑨]+)')
# 1) 讲义源文件和目录里的跨环引用
for p in sorted(glob.glob(os.path.join(HERE, '*.txt'))):
    name = os.path.basename(p)
    for i, ln in enumerate(open(p, encoding='utf-8'), 1):
        for m in ref.finditer(ln):
            for sec in expand(m.group(2)):
                chk('%s:%d' % (name, i), m.group(1), sec)
        # 目录表里「环03 细1–细6」之后紧跟的「、细7」
        for m in re.finditer(r'环(\d\d) ((?:(?:细\d+(?:[–-]细\d+)?|[①-⑨]+)[、 ]*)+)', ln):
            for tok in re.findall(r'细\d+[–-]细\d+|细\d+|[①-⑨]+', m.group(2)):
                for sec in expand(tok):
                    chk('%s:%d' % (name, i), m.group(1), sec)
# 1b) 同一环里不带环号的引用：「（细6）」「看 ⑦」「第 ⑤ 节」
for p in sorted(glob.glob(os.path.join(HERE, '环*.txt'))):
    nn = re.search(r'环(\d\d)', p).group(1)
    name = os.path.basename(p)
    for i, ln in enumerate(open(p, encoding='utf-8'), 1):
        if ln.startswith('#') or ln.startswith('@') or ' @ ' in ln:
            continue
        rest = ref.sub('', ln)
        rest = re.sub(r'环(\d\d) ((?:(?:细\d+(?:[–-]细\d+)?|[①-⑨]+)[、 ]*)+)', '', rest)
        for tok in re.findall(r'细\d+|[①-⑨]', rest):
            chk('%s:%d' % (name, i), nn, tok)
# 2) 题文件头「卡住先看：讲义 第①②节、细10、环07 讲义第③节」；3) 自测里「→ 细5」「→ ③」
for d in sorted(glob.glob(os.path.join(ROOT, '环*'))):
    nn = re.search(r'环(\d\d)', d).group(1)
    for f in sorted(glob.glob(os.path.join(d, '题*.c'))) + [os.path.join(d, '自测.c')]:
        if not os.path.exists(f): continue
        for i, ln in enumerate(open(f, encoding='utf-8'), 1):
            where = '%s:%d' % (os.path.relpath(f, ROOT), i)
            own = ln
            for m in ref.finditer(ln):
                for sec in expand(m.group(2)): chk(where, m.group(1), sec)
                own = own.replace(m.group(0), '')
            if '卡住先看' in ln or '→' in ln:
                for tok in re.findall(r'细\d+|[①-⑨]+', own):
                    for sec in expand(tok): chk(where, nn, sec)
for b in bad: print('×', b)
print('检查完：%d 个环，查了 %d 处引用，%d 处有问题' % (len(secs), nchk[0], len(bad)))
sys.exit(1 if bad else 0)
