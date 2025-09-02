# DNAの合成 (DNA Synthesizer)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2010/tasks/joisc2010_dna



# 题解

## 作者：littlebug (赞：3)

## Solution

显然是 dp。

令 $s$ 位目标串，$t_1 \sim t_n$ 为基本串。

设 $f_i$ 为构成 $s$ 的前 $i$ 位所需要的最少基本串数量，注意到基本串的长度只有 $20$，所以考虑直接枚举从哪里转移过来，如果可以从 $f_j$ 转移过来，那么显然 $f_i \gets f_j + 1$ 就行了。

这样复杂度是 $O(|s||t|)$ 的，所以考虑如何快速判断是否可以从 $f_j$ 转移过来，也就是判断 $s_{j \sim i}$ 是否在 $t$ 中出现。可以想到用 set 或者 trie 去维护。其中 set 需要 hash 一下，不然复杂度是 $O(|t| \log n)$ 的，hash 了之后复杂度就变成了 $O(|t| + \log n)$，开个 uset 应该没啥大问题。不过似乎 trie 更稳妥一些，复杂度 $O(|t|)$ 而且没什么常数。

然后在转移的时候，如果可以从 $f_j$ 转移，那么也一定可以从 $f_{j+1} \sim f_{i-1}$ 转移，因为我们 dp 状态设定的缘故所以这里要全部做一遍转移。

时间复杂度 $O(n|t|) - O(|s||t|^2)$。

## Code

用 trie 做的。

```cpp
int n,m,f[M];
string s;

struct trie
{
	struct node{int ch[4]={}; bool cnt=0;} v[N*6]; // 这里至少开 6 倍，不然会 RE
	int tot=1,to[200];
	
	trie(){to['A']=0,to['G']=1,to['C']=2,to['T']=3;}
	
	il void ins(string s)
	{
		int pos=1,now;
		for(auto c:s)
		{
			now=to[c];
			if(!v[pos].ch[now]) v[pos].ch[now]=++tot;
			pos=v[pos].ch[now];
		}
		v[pos].cnt=1;
	}
	
	il bool q(string s)
	{
		int pos=1,now;
		for(auto c:s)
		{
			now=to[c];
			if(!v[pos].ch[now]) return 0;
			pos=v[pos].ch[now];
		}
		return v[pos].cnt;
	}
} tr;

signed main()
{
	read(n),read(s),m=s.size(),s="$"+s;
	{string t; rep(i,1,n) read(t),tr.ins(t);}
	
	string tmp;
	rep(i,1,m)
	{
		tmp="",f[i]=20120712;
		rpe(j,i,max(i-20,0ll))
		{
			j && (tmp=s[j]+tmp,1);
			if(tr.q(tmp)) rep(k,j,i) f[i]=min(f[i],f[k]+1);
		}
	}
	
	write(f[m]>6737151 ? -1ll : f[m],'\n');
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

