---
title: "ADAJOBS - Ada and Jobs"
layout: "post"
diff: 省选/NOI-
pid: SP32961
tag: []
---

# ADAJOBS - Ada and Jobs

## 题目描述

As you might already know, Ada the Ladybug has a huge TODO-list. Sometimes she inserts a new job into her TODO-list and sometimes she is wondering whether there is a job (in her TODO-list), which she wants to do now. She doesn't require the whole job to be there, perhaps just a part of it.

Can you create a program which would serve her? That means it either inserts a new job into her TODO-list or answers whether there exists a word (in her TODO-list) which is a substring of given word.

## 输入格式

The first line of input containts **Q**, the number of queries.

The next **Q** lines contains a number **0 and nonempty string **s**. If **t** is equal to 0 then it is inserion query, otherwise it is question query. **s** consists of lowercase characters only.**

The sum of lengths of queries of both types doesn't exceed **10 $ ^{6} $**  (that means the total sum of lengths of strings will be at most **2\*10 $ ^{6} $** )

**NOTE:** All newly added jobs will be distinct.

## 输出格式

For each query of type **1**, print either **YES**, if there is already a substring in the TODO-list and **NO** otherwise.

