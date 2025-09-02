# マスと駒と色塗り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-qualb/tasks/codefestival_2015_qualB_d

$ 10^{100} $ 個の白いマスが横 $ 1 $ 列に並んでいます。左から $ i\ (1≦i≦10^{100}) $ 番目のマスをマス $ i $ と呼びます。

また、駒が $ N $ 個あり、$ i\ (1≦i≦N) $ 番目の駒を駒 $ i $ と呼びます。

さらに、$ 0 $ から $ 10^{100} $ までの数を数えることのできるカウンタが $ 1 $ つあります。

これらのマスと駒に対し $ N $ 回の操作を行います。$ i\ (1≦i≦N) $ 回目の操作は以下のように行います。

1. まず、マス $ S_i $ に駒 $ i $ を置き、カウンタを $ 0 $ に初期化する。
2. 駒のあるマスの色が白ならそのマスを黒に塗ってカウンタを $ 1 $ 増加させ、駒のあるマスの色が黒なら $ 1 $ つ右のマスに駒を移動させる。
3. $ 2. $ を繰り返していき、カウンタの値が $ C_i $ になったらその時点で操作を終了する。

これらの操作が終わった時点で $ N $ 個の駒がそれぞれどのマスにあるかを求めてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- 全ての操作が終わった時点での駒のあるマスの番号が全て $ 10^5 $ 以下であるデータセットに正解した場合は、$ 35 $ 点が与えられる。
- $ N\ ≦\ 1000 $ を満たすデータセットに正解した場合は、上記とは別に $ 40 $ 点が与えられる。
- 追加の制約のないデータセットに正解した場合は、上記とは別に $ 25 $ 点が与えられる。

### Sample Explanation 1

下図は各操作後のマスと駒の状態を表しています。 !\[figure1\](http://code-festival-2015-qualb.contest.atcoder.jp/img/other/code\_festival\_2015\_qualb/komasunuri.png)

### Sample Explanation 3

出力が $ 32 $ bit整数型に収まらない場合もあることに注意してください。

## 样例 #1

### 输入

```
4
3 3
10 1
4 2
2 4```

### 输出

```
5
10
7
11```

## 样例 #2

### 输入

```
8
2 1
3 1
1 1
5 1
1 1
9 1
8 2
7 9```

### 输出

```
2
3
1
5
4
9
10
18```

## 样例 #3

### 输入

```
5
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000```

### 输出

```
1999999999
2999999999
3999999999
4999999999
5999999999```

# 题解

## 作者：zhengzidu (赞：4)

# Preface
膜一下 [oyoham](https://www.luogu.com.cn/user/957618) 大佬和他介绍的题。
# Introduction

题面描述：

给你一个无限长的序列，初始全为 $0$，每次给你两个整数 $s,c$，将 $a_s$ 往后 $c$ 个非 $0$ 元素变为 $1$（包括 $a_s$）。对于每次操作，求最后一个被修改的位置的下标。

数据范围：

$1\le N \le 10^5,1\le S_i,C_i\le 10^9$。

本题有 [`set` 的做法](https://www.luogu.com/article/gexfgvx6)，本题解给出珂朵莉树的做法。

不会珂朵莉树的 [戳](https://www.luogu.com.cn/article/9hnol0ou)。

以下为本题珂朵莉树的核心代码：

```cpp
struct node{
	long long l,r;
	mutable long long val;
	node(int l,int r=0,int val=0):l(l),r(r),val(val){}
	friend bool operator<(node x,node y){
		return x.l<y.l;
	}
};
int n;
set<node> s;
set<node>::iterator split(int pos){
	set<node>::iterator it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos){
		return it;
	}
	it--;
	if(it->r<pos){
		return s.end();
	}
	long long l=it->l;
	long long r=it->r;
	long long val=it->val;
	s.erase(it);
	s.insert(node(l,pos-1,val));
	return s.insert(node(pos,r,val)).first;
}
set<node>::iterator assign(set<node>::iterator ll,set<node>::iterator rr){
	int lx=ll->l,rx=rr->r,x=ll->val;
	s.erase(ll);s.erase(rr);
	return s.insert(node(lx,rx,x)).first;
}
```

本题设计维护连续颜色段的信息，我们使用 `node(l,r,op)` 来表示区间 $[l,r]$ 的颜色为 $0$ 或 $1$并考虑维护连续的颜色为 $1$ 的颜色段信息。

每次操作时 `insert(s,s+c-1)`。当有两段 $(x_1,y_1),(x_2,y_2)$ 且 $y_1 \ge x_2$，即两段有交集时，删去这两段后插入 $(x_1,y_2+y_1-x_2)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2y44mv52.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

对于每个询问，插入新的元素后向左跳并合并跳到的合法区间即可。

```cpp
for(set<node>::iterator it=split(x);it!=s.end();++it){
			// 遍历 set 
			int l=it->l,r=it->r;
			if(!it->val){
				if(r-l+1<y){ // 变化的区间数量不足够，减去后继续遍历 
					y-=(r-l+1);it->val=1;
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
				}
				else if(r-l+1==y){ // 找到结束点了 
					it->val=1;
					write(r);printf("\n");
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
					break;
				}  
				else if(r-l+1>y){ // 当前区间节点个数多了 
					it=split(l+y);it--;
					it->val=1;
					write(it->r);printf("\n");
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
					break;
				}
			}
		}
```

其中的

```cpp
while(it->l!=1){
  set<node>::iterator itl=it;it--;
  if(it->val==itl->val){
    it=assign(it,itl);
  }
  else{
    break;
  }
}
```

就是上面说的向左跳的过程。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
struct node{
	long long l,r;
	mutable long long val;
	node(int l,int r=0,int val=0):l(l),r(r),val(val){}
	friend bool operator<(node x,node y){
		return x.l<y.l;
	}
};
int n;
set<node> s;
set<node>::iterator split(int pos){
	set<node>::iterator it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos){
		return it;
	}
	it--;
	if(it->r<pos){
		return s.end();
	}
	long long l=it->l;
	long long r=it->r;
	long long val=it->val;
	s.erase(it);
	s.insert(node(l,pos-1,val));
	return s.insert(node(pos,r,val)).first;
}
set<node>::iterator assign(set<node>::iterator ll,set<node>::iterator rr){
	int lx=ll->l,rx=rr->r,x=ll->val;
	s.erase(ll);s.erase(rr);
	return s.insert(node(lx,rx,x)).first;
}
signed main(){
	n=read();
	s.insert(node(1,1e18,0));
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		for(set<node>::iterator it=split(x);it!=s.end();++it){ 
			int l=it->l,r=it->r;
			if(!it->val){
				if(r-l+1<y){ 
					y-=(r-l+1);it->val=1;
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
				}
				else if(r-l+1==y){
					it->val=1;
					write(r);printf("\n");
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
					break;
				}  
				else if(r-l+1>y){ 
					it=split(l+y);it--;
					it->val=1;
					write(it->r);printf("\n");
					while(it->l!=1){
						set<node>::iterator itl=it;it--;
						if(it->val==itl->val){
							it=assign(it,itl);
						}
						else{
							break;
						}
					}
					break;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：oyoham (赞：1)

### Problem
给你一个无限长的序列，初始全为 $0$，每次给你 $s,c$，将 $a_s$ 往后 $c$ 个非 $0$ 元素变为 $1$（包括 $a_s$）。对于每次操作，求最后一个被修改的位置的下标。
### Solution
考虑将序列中为 $1$ 的极长连续段存储在集合 $S$ 中，每次操作时，起一段 $(s,s+c-1)$ 插进集合中，然后合并，具体的，若存在两个不同的段 $(x_a,y_a),(x_b,y_b)$ 属于 $S$ 且 $y_a\ge x_b$，则删去这两段并插入 $(x_a,y_b+y_a-x_b)$。  
注意到，只有新插入的元素能与其相邻元素合并，且合并后的元素不能与其左端点更小的元素合并，于是插入该元素后，先考虑能否与其左端点小于等于 $s$ 的第一个元素合并，再一直考虑能否向右合并。  
注意边界情况。由于总共插入 $n$ 段，每两段合成一段时段数减一，最多合并 $n-1$ 次，插入时二分每次 $\Theta(\log n)$，总时间复杂度为 $\Theta(n\log n)$。
### Code
代码中集合采用 set 实现。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
#define pint pair<int,int>
#define f first
#define s second
set<pint>S;//这里的pair<F,S>代表元素(F,F+S-1),
#define it set<pint>::iterator
int n=read();
signed main(){
	S.insert(make_pair(114514919810114514,1));
	S.insert(make_pair(-114514919810114514,1));//插入哨兵防止越界
	for(int i=1;i<=n;i++){
		int s=read(),c=read();
		pint x=make_pair(s,c);
		it I=S.lower_bound(make_pair(s,1145141919180));
		I--;
		if(I->f+I->s-1>=s){//能否向左合并
			x=*I;
			x.s+=c;
			it P=I;
			I++;
			S.erase(P);
		}
		else I++;
		//find first place behind s
		while(I->f-x.f<x.s){//能否向右合并
    //注意这里如果有(l,x)与(x+1,r)是不能合并的，最后一个修改的方格是x，所以写小于号。
			x.s+=I->s;
			it P=I;
			I++;
			S.erase(P);
		}	
		S.insert(x);//插入最后合成的元素
		write(x.f+x.s-1);putchar(10);//输出右端点
	}
}
```

---

