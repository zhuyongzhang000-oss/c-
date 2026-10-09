#!/usr/bin/env python3
"""把每环 5 道题拼成完整程序，用 gcc 编译运行，把运行结果写进 程序/输出.json。

用法：python3 公共/讲义/check_progs.py         编译运行全部，结果有变化就更新 输出.json
      python3 公共/讲义/check_progs.py 06      只跑环06
有编译警告或运行出错就报出来，退出码非 0。
"""
import json, os, shutil, subprocess, sys, tempfile

sys.dont_write_bytecode = True
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import problems

RINGS = ['%02d' % i for i in range(1, 14)]


def run_one(nn, n, program, spec):
    d = tempfile.mkdtemp(prefix='c-prog-')
    try:
        src = os.path.join(d, 'p.c')
        open(src, 'w', encoding='utf-8').write(program)
        cc = subprocess.run(['gcc', '-std=c99', '-Wall', '-Wextra', '-Wno-unused-parameter', '-o', os.path.join(d, 'p'), src, '-lm'],
                            capture_output=True, text=True)
        if cc.returncode != 0 or cc.stderr.strip():
            return None, '编译：\n' + cc.stderr
        for name, lines in spec['files'].items():
            open(os.path.join(d, name), 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
        stdin = '\n'.join(spec['input']) + ('\n' if spec['input'] else '')
        r = subprocess.run([os.path.join(d, 'p')], input=stdin, capture_output=True, text=True, cwd=d, timeout=10)
        if r.returncode != 0:
            return None, '运行返回 %d\n%s' % (r.returncode, r.stderr)
        files = {}
        for name in spec['show']:
            p = os.path.join(d, name)
            files[name] = open(p, encoding='utf-8').read() if os.path.exists(p) else None
            if files[name] is None:
                return None, '没有生成文件 ' + name
        return {'out': r.stdout, 'files': files}, ''
    finally:
        shutil.rmtree(d, ignore_errors=True)


def main():
    only = sys.argv[1:] or RINGS
    data = problems.load_outputs()
    bad = 0
    for nn in only:
        for n, hd, tip, program, spec in problems.ring_problems(nn):
            res, err = run_one(nn, n, program, spec)
            key = '%s-%d' % (nn, n)
            if err:
                bad += 1
                print('✗ 环%s 题%d：%s' % (nn, n, err))
                continue
            if data.get(key) != res:
                data[key] = res
                print('· 环%s 题%d 输出已更新' % (nn, n))
    json.dump(data, open(problems.OUT_JSON, 'w', encoding='utf-8'), ensure_ascii=False, indent=1, sort_keys=True)
    print('完整程序检查完：%d 个环，%d 个有问题' % (len(only), bad))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
