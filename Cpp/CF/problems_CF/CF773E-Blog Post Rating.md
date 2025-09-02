---
title: "Blog Post Rating"
layout: "post"
diff: 省选/NOI-
pid: CF773E
tag: []
---

# Blog Post Rating

## 题目描述

It's well-known that blog posts are an important part of Codeforces platform. Every blog post has a global characteristic changing over time — its community rating. A newly created blog post's community rating is 0. Codeforces users may visit the blog post page and rate it, changing its community rating by +1 or -1.

Consider the following model of Codeforces users' behavior. The $ i $ -th user has his own estimated blog post rating denoted by an integer $ a_{i} $ . When a user visits a blog post page, he compares his estimated blog post rating to its community rating. If his estimated rating is higher, he rates the blog post with +1 (thus, the blog post's community rating increases by 1). If his estimated rating is lower, he rates the blog post with -1 (decreasing its community rating by 1). If the estimated rating and the community rating are equal, user doesn't rate the blog post at all (in this case we'll say that user rates the blog post for 0). In any case, after this procedure user closes the blog post page and never opens it again.

Consider a newly created blog post with the initial community rating of 0. For each of $ n $ Codeforces users, numbered from 1 to $ n $ , his estimated blog post rating $ a_{i} $ is known.

For each $ k $ from 1 to $ n $ , inclusive, the following question is asked. Let users with indices from 1 to $ k $ , in some order, visit the blog post page, rate the blog post and close the page. Each user opens the blog post only after the previous user closes it. What could be the maximum possible community rating of the blog post after these $ k $ visits?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the number of Codeforces users.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -5·10^{5}<=a_{i}<=5·10^{5} $ ) — estimated blog post ratings for users in order from 1 to $ n $ .

## 输出格式

For each $ k $ from 1 to $ n $ , output a single integer equal to the maximum possible community rating of the blog post after users with indices from 1 to $ k $ , in some order, visit the blog post page, rate the blog post, and close the page.

## 样例 #1

### 输入

```
4
2 0 2 2

```

### 输出

```
1
1
2
2

```

## 样例 #2

### 输入

```
7
2 -3 -2 5 0 -3 1

```

### 输出

```
1
0
-1
0
1
1
2

```

