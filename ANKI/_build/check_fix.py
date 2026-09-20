# -*- coding: utf-8 -*-
"""定点复核两张修复目标卡片。"""
import json, re, sqlite3, zipfile, os
APKG = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\13003数据结构与算法-大纲考点.apkg"
TMP = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\verify_tmp"
with zipfile.ZipFile(APKG) as z:
    z.extract("collection.anki2", TMP)
con = sqlite3.connect(os.path.join(TMP, "collection.anki2"))
cur = con.cursor()
models = json.loads(cur.execute("SELECT models FROM col").fetchone()[0])
names = [f["name"] for f in list(models.values())[0]["flds"]]
targets = ["数据元素", "冲突解决方法"]
for nid, flds in cur.execute("SELECT id, flds FROM notes"):
    parts = flds.split("\x1f")
    field = dict(zip(names, parts))
    if field.get("知识点") in targets:
        print("== 知识点:", field["知识点"], "| 小结:", field["小结"])
        print("正面:", re.sub(r"<[^>]+>", "", field["描述填空"])[:150])
        print("反面:", re.sub(r"<[^>]+>", "", field["描述答案"])[:150])
        print("答案:", field["挖空答案"], "| 页码:", field["页码"])
        print()
con.close()
