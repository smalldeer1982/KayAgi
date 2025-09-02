---
title: "ZZPERM2 - Zig-Zag Permutation 2"
layout: "post"
diff: 难度0
pid: SP11946
tag: []
---

# ZZPERM2 - Zig-Zag Permutation 2

## 题目描述

请参阅 [ZZPERM](../ZZPERM/) 问题描述。这是该问题的一个改进版本，并且包含更具挑战性的测试用例。

## 输入格式

输入最多包含 15 组测试数据。每组测试数据由一个由字母按字典序排列的单词 $W$ 和一个正整数 $D$（其中 $D \leq 1000000000$）组成。单词 $W$ 的长度不超过 64 个字符。输入以文件结尾（EOF）结束。

## 输出格式

对于每组数据，输出每个能够被 $D$ 整除的、按字典序递增排列的 $W$ 的“zig-zag”排列。每行输出一个排列单词。接下来的一行，输出 $W$ 的所有可能“zig-zag”排列的总数。任何一组数据的输出行数不会超过 365 行。每组数据输出完毕后，请输出一个空行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
j 1
abc 2
aaabc 1
aaabb 2
aaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbcccdd 123456
aaaaaaaaabbbbbbbbbcccccccccddddddddd 1000000000
```

### 输出

```
j
1

bac
cab
4

abaca
acaba
2

1

babacbcabacabadabababababababababadab
213216

abacbcacbdadcdbcadbdacbdacbdadbcbcad
abadadcdcdcdbdbdadbcabacacbdbcbcacab
acabacbcbdbcbdcdadadacbcadbcbcadadbd
acacbcbdacbdcdacbcadbdbcbcadadbdabad
acadbcadbdbcacadbdbcacbdbdacbdbcadac
acbcacbcadbdadadadbcbdcdabacacbdbdbc
acbcbdadbdcdbcbcbcacbdadadadadbcacab
acbdadcdcdadadbdababacbcbcbcacbdbdac
acbdcdbdbcacbcbcadabadbcabadbdcdacad
adacbcacbcbcbdcdcdbdadadabadbdbcacab
adadbcbcadbcabacadbdbcbdabadcdcdacbc
adbcadbcabacbdacacbcbcbdcdadbdadbdac
adbdacababacadadcdbcbcadbdacbcbdcdbc
adbdcdacbdbcbdbcadadadbcadacbcacbcab
adcdbdacadacbdbcbdadacbcbcadbdbcacab
babacbdcdbdcdbcadcdbcabacacadadbdacb
bacacadbdcdbcbdbdcdacbdacabacadbcadb
bacadcdbcbdabacbcacacadadadcdbdbdbcb
bacbdadacabacadacbdcdbcadbcbdbcbdadc
badacadbcadacbcbdadbdbcacbcbdcdabadc
badbcacbdabadcdbcadbdacabacbdacbdcdc
badbdcdbdadacbcbcacacbdbdacbdadbcaca
bcabacadbdbdacacbdadcdadbcbcbcadacbd
bcacadacbcbdcdbdbcbdbdadadabacbdacac
bcacbdbdcdcdababadacbcadacacbdbdbcad
bcadbcadbdbdcdcdadbcbcacbcababadacad
bcbcabadacadcdadacbdadbcbdcdbcacbdab
bcbcbcadbcadbcadbdadbcbcadabacadadcd
bcbdacbdacbdbcbdadacacbdcdbdadacabac
bcbdbdbdcdacacacbdbcadadbcababacadcd
bdabadcdbdadbcadcdbcbdcdbcabacabacac
bdacbcbcbcadadbcadcdabadbcacbdcdabad
bdadbcabacbcbcababadacadcdcdbdcdacbd
bdbcacacbdbcadbcbdabacbcadacadadbdcd
bdbcbdacacbdadbdcdababadadcdbcacbcac
bdbdbcadbcacadbcadacadbdbdcdbcacacab
bdcdacbdadadbcbcacacbcacabadbdbcadbd
bdcdcdadacadcdbdbcababadbcacbcadbcab
cabacbdcdbdadacacadbcbcacadbcbdbdadb
cacabadcdbdbdbcbcbdacabadbdacbdacadc
cacadcdbcbcbdcdacababacbcadbdbdbdada
cacbdadbdadacbdababacbcbdcdcdcdabacb
cadacadbdabacbcacbdbdcdadbcadadbcbcb
cadbcacbcbdcdbdbcadbcbdadabacbdacada
cadbdbcbdacadbdacadacbdbcbcadbcabadc
cbcabacbcbdadabacbcadbdadcdcdadacbdb
cbcadacadadbdbcacbcadbdbdacbcabadcdb
cbcbcadacbcadadadbcbdacadbcbdbdacadb
cbcbdbcadcdacbdadacbdbcacadacbdabadb
cbdacadacbcbdcdbdabadbcbcacabadcdadb
cbdadbdadabadcdabadcdacbcbcabacbcbdc
cbdbcbdcdbcbdacacbdadadcdababacabadc
cbdcdacbdbcbdadacacadbcabababadcdbdc
cdabadacabadcdbdcdbdbcabadbcbcacadbc
cdacbcbcadabadcdbdbcbcacbdadadabadbc
cdadbcacacbcadadbdbdbcabadbcbcbcadad
cdbcacadbcbdbcadbdadadbdbcacbcadabac
cdbcbdadadacbdbcabacbcbcabadacadcdbd
cdbdbcabadcdbdbdcdacacababadbdacacbc
cdcdacacbcadbcabadbdcdbcbcabadadbdab
dababacbcbcadbdacacbcacbdbdcdadcdadb
dabadbdcdacacadabadcdbdbcbcbcacbdbca
dacadacbdbdbcacbcadbdbcacbcadbdcdaba
dacbcbdadadcdbdacadcdababacbcacbdbcb
dadabadbcbcadcdbdacbcadacadbcbcbdbca
dadbcadadbdcdcdabacbcbdbcacbdbcabaca
dadcdbcacabadadbcabadbcadcdadbcbcbcb
dbcacbcadacadbcacbdadacbcbdacbdbdadb
dbcadcdbcbdbdadbdadbcacbcacacbcabada
dbcbdacbcadbdacbdadbdacbcadbcacadacb
dbdacacbdadbcbcbcbcadbdadbcadbcadaca
dbdbcacadacabacbcadacbdadcdbdbdbcbca
dbdcdabacadadbcbdcdbcacacbcbdbdacaba
dcdacadadbcbcabacbcacbdbcbdbcadadadb
dcdbcadadbcbcadbcbcadabadbdcdbcacaba
dcdcdacabadbdbdacacbcacbdababadbcbdc
76317369490
```

