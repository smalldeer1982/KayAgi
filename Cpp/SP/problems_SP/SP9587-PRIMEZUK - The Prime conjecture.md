---
title: "PRIMEZUK - The Prime conjecture"
layout: "post"
diff: 普及-
pid: SP9587
tag: []
---

# PRIMEZUK - The Prime conjecture

## 题目描述

Euclid may have been the first to prove that there are infinitely many primes. Let's walk through his proof, as even today, it's regarded as an excellent model of reasoning.

Let us assume the converse, that there only a finite number of primes: p $ _{1} $ , p $ _{2} $ , ..., p $ _{n} $ . Let **m** = 1 + $ _{i=1} $ Π $ ^{n&nbsp;} $ p $ _{i,} $ i.e. the product of all of these primes plus one. Since this number is bigger than any of the primes on our list, m must be composite. Therefore, some prime must divide it. But which prime? In fact, m leaves a reminder of 1 when divided by any prime p $ _{i} $ , for 1 <= i <= n. Thus, p $ _{1} $ , p $ _{2} $ , ..., p $ _{n} $ cannot be the complete list of primes, because if so m must also be a prime. Since this contradicts the assumption it means there cannot exist such a complete list of primes; therefore the number of primes must be infinite!

Your mathematician friend Wannabe\_Fermat has come up with a conjecture which he keeps telling to anyone who is willing to lend an ear: "The number **m** that we come up with when multiplying any **n** distinct prime numbers and adding 1 to this result is also a prime". You as Wannabe\_Zuckerburg, are becoming jealous as your friend's conjecture is gaining popularity and decide to come up with a program that finds counter-examples to shut him up forever.

## 样例 #1

### 输入

```
2
3
2 3 5
4
2 7 5 11
```

### 输出

```
Case #1: 31
Case #2: 257
```

