# Sequence Recovery

## 题目描述

Zane once had a good sequence $ a $ consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ — but he has lost it.

A sequence is said to be good if and only if all of its integers are non-negative and do not exceed $ 10^{9} $ in value.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796F/7c34d2981d5a0342e098e7b1d14d4ca5448e48f2.png)However, Zane remembers having played around with his sequence by applying $ m $ operations to it.

There are two types of operations:

1\. Find the maximum value of integers with indices $ i $ such that $ l<=i<=r $ , given $ l $ and $ r $ .

2\. Assign $ d $ as the value of the integer with index $ k $ , given $ k $ and $ d $ .

After he finished playing, he restored his sequence to the state it was before any operations were applied. That is, sequence $ a $ was no longer affected by the applied type 2 operations. Then, he lost his sequence at some time between now and then.

Fortunately, Zane remembers all the operations and the order he applied them to his sequence, along with the distinct results of all type 1 operations. Moreover, among all good sequences that would produce the same results when the same operations are applied in the same order, he knows that his sequence $ a $ has the greatest cuteness.

We define cuteness of a sequence as the bitwise OR result of all integers in such sequence. For example, the cuteness of Zane's sequence $ a $ is $ a_{1} $ OR $ a_{2} $ OR ... OR $ a_{n} $ .

Zane understands that it might not be possible to recover exactly the lost sequence given his information, so he would be happy to get any good sequence $ b $ consisting of $ n $ integers $ b_{1},b_{2},...,b_{n} $ that:

1\. would give the same results when the same operations are applied in the same order, and

2\. has the same cuteness as that of Zane's original sequence $ a $ .

If there is such a sequence, find it. Otherwise, it means that Zane must have remembered something incorrectly, which is possible.

## 说明/提示

In the first sample, it is easy to verify that this good sequence is valid. In particular, its cuteness is $ 19 $ OR $ 0 $ OR $ 0 $ OR $ 0 $ OR $ 1 $ $ = $ $ 19 $ .

In the second sample, the two operations clearly contradict, so there is no such good sequence.

## 样例 #1

### 输入

```
5 4
1 1 5 19
1 2 5 1
2 5 100
1 1 5 100
```

### 输出

```
YES
19 0 0 0 1
```

## 样例 #2

### 输入

```
5 2
1 1 5 0
1 1 5 100
```

### 输出

```
NO```

# 题解

## 作者：KaisuoShutong (赞：3)

先正向处理一遍，判断每个区间是否必须取到最大值（存在某个修改后的值等于最大值）/是否非法（存在某个修改后的值大于最大值）。可以开一颗单改区查线段树。

再逆向处理一遍，维护出每个下标所能取到的最大值。值得注意的是如果遍历到一个修改操作，说明在此之后的限制都是无意义的，需要清掉。可以开一颗区改线段树。

最后遍历所有区间，随机钦定一个下标能取到的最大值为当前区间最大值的下标为该值。如果没有则无解。因为保证了所有区间的权值都不同，所以可以这样做。

这时还剩一些下标没有钦定，分别是有限制的和完全没有限制的（也就是限制为 $10^9$）的。对于有限制的，若限制为 $v$，直接选择 $2^{\lfloor\log_2v\rfloor}-1$ 一定是最优的，因为 $\lfloor\log_2v\rfloor$ 位一定被钦定的选择了。

没有限制的最后处理，先处理出当前的答案，然后从高到低位贪心选一下即可。

```cpp
for(int i=1,t;i<=m;i++)
		if((ty[i]=read())==1) {
			L[i]=read(),R[i]=read(),V[i]=read();
			t=MAX::ask(1,1,n,L[i],R[i]);
			if(t>V[i]) NO();else if(t<V[i]) lim[i]=1;
		}
		else L[i]=read(),MAX::ins(1,1,n,L[i],V[i]=read());
	for(int i=m;i;i--)
		if(ty[i]==1) MIN::ins(1,1,n,L[i],R[i],V[i]);
		else MIN::upd(1,1,n,L[i]);
	MIN::byd(1,1,n);
	for(int i=1;i<=n;i++) mp[w[i]]=1;
	for(int i=1;i<=m;i++)
		if(ty[i]==1&&lim[i]) {
			if(!mp[V[i]]) NO();
		}
	mp.clear();
	for(int i=1;i<=n;i++) if(w[i]^inf) {
		if(!mp[w[i]]) a[i]=w[i],mp[w[i]]=1;
		else a[i]=(1<<(int)log2(w[i]))-1;
		all|=a[i];
	}cout<<"YES\n";
	for(int i=1;i<=n;cout<<a[i++]<<' ') if(w[i]==inf) {
		for(int j=30;~j;j--) if(!(all>>j&1)) {
			if(a[i]+(1<<j)<=1e9) a[i]+=(1<<j);
		}all|=a[i];
	}
```

---

