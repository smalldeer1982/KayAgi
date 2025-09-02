---
title: "Palindromic Times"
layout: "post"
diff: 普及-
pid: CF108A
tag: []
---

# Palindromic Times

## 题目描述

Tattah is asleep if and only if Tattah is attending a lecture. This is a well-known formula among Tattah's colleagues.

On a Wednesday afternoon, Tattah was attending Professor HH's lecture. At 12:21, right before falling asleep, he was staring at the digital watch around Saher's wrist. He noticed that the digits on the clock were the same when read from both directions i.e. a palindrome.

In his sleep, he started dreaming about such rare moments of the day when the time displayed on a digital clock is a palindrome. As soon as he woke up, he felt destined to write a program that finds the next such moment.

However, he still hasn't mastered the skill of programming while sleeping, so your task is to help him.

## 输入格式

The first and only line of the input starts with a string with the format "HH:MM" where "HH" is from "00" to "23" and "MM" is from "00" to "59". Both "HH" and "MM" have exactly two digits.

## 输出格式

Print the palindromic time of day that comes soonest after the time given in the input. If the input time is palindromic, output the soonest palindromic time after the input time.

## 样例 #1

### 输入

```
12:21

```

### 输出

```
13:31

```

## 样例 #2

### 输入

```
23:59

```

### 输出

```
00:00

```

