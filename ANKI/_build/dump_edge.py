# -*- coding: utf-8 -*-
"""查看无描述(E为空)与无挖空的卡片行详情。"""
import json
ROWS = json.load(open(r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\rows.json", encoding="utf-8"))
print("== E 为空但 D 非空的行 ==")
for r in ROWS:
    d = r["knowledge"].strip()
    if d and not r["desc"].strip():
        print("行%s | A=%r | B=%r | D=%r | C=%r | G=%r" % (
            r["excel_row"], r["chapter"].strip(), r["requirement"].strip(),
            d, r["summary"].strip()[:80], r["page"]))
print("\n== E 很短(<=12字)的行 ==")
for r in ROWS:
    e = r["desc"].strip()
    if len(e) <= 12 and e:
        print("行%s | D=%r | E=%r" % (r["excel_row"], r["knowledge"].strip(), e))
