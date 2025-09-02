---
title: "WSCIPHER - Ws Cipher"
layout: "post"
diff: 难度0
pid: SP899
tag: []
---

# WSCIPHER - Ws Cipher

## 题目描述

Weird Wally's Wireless Widgets, Inc. 专门生产各种小型无线设备，从狗项圈到铅笔再到鱼漂，这些设备都具备联网功能。但由于这些设备内存很小，无法使用像 Rijndael 这样的大型加密算法。为了传输安全，该公司设计了一种简单的加密算法，你需要对此进行实现。

加密一条信息需要三个整数密钥 $k_1$、$k_2$ 和 $k_3$。字母 \[a-i\] 属于第一组，\[j-r\] 属于第二组，其余字符（\[s-z\] 和下划线）为第三组。在每组内部，字母根据对应的密钥 $k_i$ 向左旋转。每个组的加密互相独立。解密操作则是每组内的字母依据 $k_i$ 向右旋转。

举例来说，消息 "the_quick_brown_fox" 使用 $k_1=2, k_2=3, k_3=1$ 加密后变为 "_icuo_bfnwhoq_kxert"。下图展示了解密时每组字符右旋的过程。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP899/8583cdcb46a9a46aecaf4d014176faac07da36c3.png)

以 [a-i] 组为例，加密后字母 {i,c,b,f,h,e} 出现在位置 {2,3,7,8,11,17}。经过 $k_1=2$ 的右旋后，位置上字母变为 {h,e,i,c,b,f}。下表显示了依次旋转第一组、第二组和第三组后的中间结果。每组旋转只影响该组内的字符，不会改变其他组的字符。

\[a-i\], $k_1$ = 2  
\[j-r\], $k_2$ = 3  
\[s-z\] 和下划线，$k_3$ = 1  
Encrypted: \_icuo\_bfnwhoq\_kxert  
Intermediate: \_heuo\_icnwboq\_kxfrt  
Intermediate: \_heuq\_ickwbro\_nxfot  
Decrypted: the\_quick\_brown\_fox  

变化示例:  
` ^^   ^^  ^     ^  `  
`    ^   ^  ^^ ^  ^  `  
`^  ^ ^   ^   ^ ^  ^  `

所有输入字符串仅包含小写字母和下划线（\_）。每个字符串长度最多为80个字符。密钥 $k_i$ 为1到100的正整数。

## 输入格式

输入包括多组测试数据。每组以一行三个整数 $k_1, k_2, k_3$ 开始，接着是一行加密消息。遇到三密钥均为0的行标识输入结束。

## 输出格式

对每组加密信息，输出一行对应的解密结果。

**示例输入**

```
2 3 1
_icuo_bfnwhoq_kxert
1 1 1
bcalmkyzx
3 7 4
wcb_mxfep_dorul_eov_qtkrhe_ozany_dgtoh_u_eji
2 4 3
cjvdksaltbmu
0 0 0
```

**示例输出**

```
the_quick_brown_fox
abcklmxyz
the_quick_brown_fox_jumped_over_the_lazy_dog
ajsbktcludmv
```

 **本翻译由 AI 自动生成**

