---
title: "MESS - Messy Administration"
layout: "post"
diff: 难度0
pid: SP7403
tag: []
---

# MESS - Messy Administration

## 题目描述

2010 年秋季学期，EPFL 迎来了 2,300 名新生。为这些新生办理不同专业和年级的注册工作是个巨大的挑战。本来这个过程已经非常自动化，一直运行良好，直到今年……

处理注册的软件没有预见到这么大量的新生，导致秘书们收到注册打印件时几乎崩溃。本应该打印出每个班级（根据专业和年级，如建筑学，本科一年级）注册学生名单的列表，结果却打印成了五种不同格式的句子：

- ! _STUDENT\_ID1_ 学习 _SECTION_
- ! _STUDENT\_ID1_ 进入学期 _SEMESTER_
- ! _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 选择相同的专业
- ! _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 在同一个学期
- ! _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 在同一个班级

其中 _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 是 6 位数的学号，_SEMESTER_ 是介于 1 到 10 之间的整数，_SECTION_ 是一个单词。

秘书们非常困惑，不知道如何从这些打印件中恢复到预期的名单。不过，幸好他们想起了 PolyProg。于是，他们把这些打印件交给了你，希望你能帮忙回答一些急切的问题。

你需要回答的问题包括：

- ? _STUDENT\_ID1_ 学习的是什么专业
- ? _STUDENT\_ID1_ 将进入哪个学期
- ? _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 是否是同班同学

如果两个学生学习相同的专业并进入同一学期，则可认为他们是同班同学。为了尽力回答，你的答案必须尽可能详细。不能提供错误的答案，如果信息不足以回答某个问题，则需承认。

答案需遵循以下优先级：

- 对于 "What does _STUDENT\_ID1_ study"（_STUDENT\_ID1_ 学习什么专业）

  - _STUDENT\_ID1_ 学习 _SECTION_
  - 对不起，目前还不清楚

- 对于 "Which semester will _STUDENT\_ID1_ enter"（_STUDENT\_ID1_ 将进入哪个学期）

  - _STUDENT\_ID1_ 进入学期 _SEMESTER_
  - 对不起，目前还不清楚

- 对于 "Are _STUDENT\_ID1_ and _STUDENT\_ID2_ classmates"（_STUDENT\_ID1_ 和 _STUDENT\_ID2_ 是同班同学吗）

  - 是的，_STUDENT\_ID1_ 和 _STUDENT\_ID2_ 是同班同学
  - 不，这不可能
  - 可能，前提是 _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 学习相同的专业
  - 可能，前提是 _STUDENT\_ID1_ 和 _STUDENT\_ID2_ 在同一个学期
  - 对不起，目前还不清楚

## 输入格式

输入包含一个测试用例，由不超过 1,000 个打印句子和最多 500 个问题组成。这些句子和问题可能混合在一起，你需要按顺序处理。回答一个问题时，不能依赖列表中后续的信息。你可以假设句子之间没有矛盾！输入在一行中以单词 END 结束。

## 输出格式

输出你的答案，每行一个，并以换行符结束。注意避免拼写错误。

**样例输入**
```
! 166554 and 175129 chose the same studies
! 175129 and 170113 are in same semester
! 166554 studies electronics
! 169983 and 170113 chose the same studies
? Are 170113 and 169983 classmates
! 169983 enters semester 9
! 175129 and 169983 are in same semester
? Which semester will 170113 enter
? Are 169983 and 170113 classmates
? Which semester will 166554 enter
? What does 175129 study
! 169983 studies communicationsystems
? Are 166554 and 169983 classmates
END
```

**样例输出**
```
Possible, given that 170113 and 169983 study the same subject
170113 enters semester 9
Yes, 169983 and 170113 are classmates
Sorry, I have no clue yet
175129 studies electronics
No, this is not possible
```

 **本翻译由 AI 自动生成**

