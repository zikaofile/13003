# -*- coding: utf-8 -*-
"""检查数据元素卡片的原始字段与挖空位置。"""
import json, re, sqlite3, zipfile, os
APKG = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\13003数据结构与算法-大纲考点.apkg"
TMP = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\verify_tmp"
with zipfile.ZipFile(APKG) as z:
    z.extract("collection.anki2", TMP)
con = sqlite3.connect(os.path.join(TMP, "collection.anki2"))
cur = con.cursor()
models = json.loads(cur.execute("SELECT models FROM col").fetchone()[0])
for mid, m in models.items():
    names = [f["name"] for f in m["flds"]]
    break
for nid, flds in cur.execute("SELECT id, flds FROM notes"):
    parts = flds.split("\x1f")
    field = dict(zip(names, parts))
    if field.get("知识点") == "数据元素":
        print("知识点:", field["知识点"])
        print("正面字段原文:", repr(field["描述填空"][:200]))
        print("反面字段原文:", repr(field["描述答案"][:200]))
        print("答案:", field["挖空答案"])
        break
con.close()

# 对照源数据行
ROWS = json.load(open(r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\rows.json", encoding="utf-8"))
for r in ROWS:
    if r["excel_row"] == 4:
        print("\n源行4 E原文:", repr(r["desc"][:120]))
        break
