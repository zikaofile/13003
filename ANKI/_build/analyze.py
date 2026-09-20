# -*- coding: utf-8 -*-
"""抽样分析 E 描述文本，评估挖空策略。"""
import json, re, collections

ROWS = json.load(open(r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\rows.json", encoding="utf-8"))
data = [r for r in ROWS if r["desc"].strip()]

# 1) E 文本长度分布
lens = [len(r["desc"]) for r in data]
print("E长度: min=%d max=%d avg=%.1f" % (min(lens), max(lens), sum(lens)/len(lens)))

# 2) 引号片段统计
qpat = re.compile(r"[“\"]([^”\"]{1,30})[”\"]")
quoted = collections.Counter()
for r in data:
    for m in qpat.finditer(r["desc"]):
        quoted[m.group(1)] += 1
print("\n出现>=2次的引号片段TOP40:")
for k, v in quoted.most_common(40):
    print("  %3d  %s" % (v, k))

# 3) 每个章节抽2条样例
seen = {}
for r in data:
    ch = r["chapter"].strip()
    if ch not in seen:
        seen[ch] = []
    if len(seen[ch]) < 2:
        seen[ch].append(r)
print("\n各章样例:")
for ch, rows in seen.items():
    for r in rows:
        print("【%s|%s|%s】D=%s" % (ch, r["requirement"], r["summary"], r["knowledge"]))
        print("  E=%s" % r["desc"][:150])
        print("  页码=%s" % r["page"])
