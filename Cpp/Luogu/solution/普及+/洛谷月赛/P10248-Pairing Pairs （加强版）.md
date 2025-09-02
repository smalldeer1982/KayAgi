# Pairing Pairs （加强版）

## 题目背景

本题是 [Pairing Pairs](https://www.luogu.com.cn/problem/P10247) 的加强版，数据范围和输入输出方式都有区别。

## 题目描述

你有一些数对 $(u_i,v_i)$（保证 $0\le u_i<v_i<n$ 且数对两两不同），对于每个 $i$ 找一个 $j$ 使得 $u_i,v_i,u_j,v_j$ 四个数两两不同，或报告不存在。

**为加速输入输出，本题采用 grader 交互。请注意本题和赛时题目的区别，本题输入和输出的下标均从 $0$ 开始。**

你需要实现一个函数 `int* find_pairs(int n,int m,int u[],int v[])`，其中 $n,m,u,v$ 如题意所示。

返回值是一个数组（设为 `ans`），则 `ans[i]` 表示你对于 $i$ 找到的 $j$。若这样的 $j$ 不存在，则 `ans[i]=-1`，**不是 $0$。**

**由于本题的返回值是一个指针，请保证返回的数组在堆空间中，具体可以参考[这篇博客](https://www.luogu.com.cn/article/sxyv0830)。**

## 说明/提示

【样例解释】

根据该程序，样例交互库将会调用 `find_pairs(7,5,{0,2,0,2,3},{2,3,3,5,6})`，然后如果你返回的数组是 `{4,-1,3,4,0}`，就会得到样例输出。这个样例输出是合法的。

【数据范围】

对于全体数据，保证 $1\le n,m\le 10^7$。

std 用时为 $324$ 毫秒，空间为 $267.87$ MB。

## 样例 #1

### 输入

```
7 5
0 2
2 3
0 3
2 5
3 6```

### 输出

```
4 -1 3 4 0
```

# 题解

## 作者：elbissoPtImaerD (赞：5)

本题主要考察的知识点：【9】构造思想。

比较好写的线性做法。

不妨考虑那 $0$ 作为每个点的答案，显然会有若干点不合法， 不妨先考虑 $\forall i, u_0 \in \{u_i,v_i\}$ 的答案。考虑再找一个 $j$ 使得 $j$ 是 $i$ 的答案。首先显然不能找 $u_0 \in \{u_j,v_j\}$ 的 $j$，再随便从剩下的找一个 $j$，那么不能以 $0$ 和 $j$ 作为答案的 $i$ 必然满足 $(u_i \in \{u_j,v_j\}\wedge v_i=x_0)\vee(u_i=x_0 \wedge v_i \in \{u_j,v_j\})$，这样的显然只有 $O(1)$ 个，直接暴力扫答案即可。

```cpp
extern "C" int*find_pairs(int m,int n,int u[],int v[]) {
  int*ans=new int[n];
  fill(ans,ans+n,-1);
  const auto chk=[&](int i,int j) {
    if(u[i]!=u[j]&&u[i]!=v[j]&&v[i]!=u[j]&&v[i]!=v[j]) {
      ans[i]=j,ans[j]=i;
      return true;
    }
    return false;
  };
  ve<int>b[2],p[2];
  for(int i=1;i<n;++i) {
    if(chk(0,i)) p[0].pb(i),p[1].pb(i);
    else b[u[i]!=u[0]].pb(i),p[u[i]==u[0]].pb(i);
  }
  for(int _:{0,1}) if(p[_].size()) {
    for(int i:b[_]) if(!chk(i,p[_][0])) {
      for(int j:p[_]) if(chk(i,j)) break;
    }
  }
  return ans;
}
```

---

## 作者：yummy (赞：5)

本题涉及的主要知识点：

- 【3】图的定义和相关概念
- 【4】图的表示与存储：邻接表

本题为加强版的题解，其中文字分析部分和原版完全一致。

---

看到数对，一个很合理的想法是把它转化成图论问题，也就是给出一张无向图，对于每一条边 $i$，找另一条边 $j$ 使得 $i,j$ 没有公共点。

根据直觉，限制条件只有几个不等式，是个很宽松的条件。我们能不能从图上找一些边，然后直接一劳永逸了呢？

（我估计具体的选法会非常多，我的做法很可能不是最简单的，仅供参考）

### Part 1 四点链

如果图上存在 $A-B-C-D$ 的结构（我称为四点链），那么对于每条边：

- 如果两端点都不是 $A,B,C,D$ 之一，那么随便挑一条边即可。
- 如果两端点中恰有一个是 $A$ 或 $B$，则选 $C-D$ 这条边即可。$C,D$ 同理。
- 如果两端点都是 $A,B,C,D$ 之一，那么**这样的边不超过 $6$ 条**，直接 $O(m)$ 做就行。

事实上哪怕 $A,D$ 重合了（三角形），我们也可以使用类似的方法进行推理，所以**只要**能找到三条不同的边 $P,Q,R$ 满足 $P,Q$ 和 $Q,R$ 分别交于 $Q$ 的两端点，**就能**在 $O(m)$ 的时间内找出答案。

---

寻找四点链，可以枚举边 $Q$。如果某条边 $Q$ 的两端**度数**均 $\ge 2$，那么我们一定能找出一对 $P,R$。

~~这里你需要使用邻接表或 `vector` 记录和每个点相邻的点和对应的边编号。~~

`vector` 太慢了，但是我们注意到每个点我们只需要用到连着它的**任意**两条边，因此可以使用普通数组。

### Part 2 菊花图森林

如果很不幸，你没有找到四点链，怎么办？

一张图没有四点链，那么一定是若干个菊花图（也就是一个中心直接连接了若干个其它结点）放在一起。

如果整张图里只有一个菊花图，那么显然大家都无法成功配对（所有边都连接了中心）。

如果有至少两个菊花图，那么每条边都和**另一个菊花图**里的边配对即可。

实现的时候不一定要找出两个菊花图，只需要任取一条边，找一下是否有第二条边和它没有公共点，如果有，那么它们肯定来自不同菊花图。

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[10000005],lst[10000005];
int P=-1,Q=-1,R=-1;
bool well(int u1,int v1,int u2,int v2){
	if(u1<u2)return v1!=u2 && v1!=v2;
	return u1!=u2 && v2!=u1 && v2!=v1;
}
extern "C" int* find_pairs(int n,int m,int u[],int v[]){
	memset(lst,-1,sizeof lst);
	for(int i=0;i<m;i++){
		if(lst[u[i]]>=0 && lst[v[i]]>=0){
			Q=i;
			P=lst[u[i]];
			R=lst[v[i]];
			break;
		}
		lst[u[i]]=i;
		lst[v[i]]=i;
	}
	if(Q==-1){
		for(int i=1;i<m;i++)
			if(well(u[0],v[0],u[i],v[i])){
				Q=i;
				break;
			}
		if(Q==-1)memset(ans,-1,4*m);
		else
			for(int i=0;i<m;i++)
				if(well(u[0],v[0],u[i],v[i]))
					ans[i]=0;
				else ans[i]=Q;
		return ans;
	}
	else{
		for(int i=0;i<m;i++)
			if(well(u[P],v[P],u[i],v[i]))ans[i]=P;
			else if(well(u[Q],v[Q],u[i],v[i]))ans[i]=Q;
			else if(well(u[R],v[R],u[i],v[i]))ans[i]=R;
			else{
				ans[i]=-1;
				for(int j=0;j<m;j++){
					if(well(u[i],v[i],u[j],v[j])){
						ans[i]=j;
						break;
					}
				}
			}
		return ans;
	}
}
```

---

## 作者：shuqiang (赞：3)

设第 $i$ 个数对包含 $p_i,q_i$ 且 $p_i \ne q_i$ （为了方便，这里不保证 $p_i < q_i$），考虑根据第一个数对和其他数对的关系分成 $4$ 组：
1. $p_1=p_i \land q_1=q_i$
2. $p_1=p_i \land q_1 \ne q_i$
3. $p_1 \ne p_i \land q_1=q_i$
4. $p_1 \ne p_i \land q_1 \ne q_i$


然后分类讨论，首先第一组的答案可以在第四组中任选，第四组的答案在第一组中任选。

考虑第二组，显然如果第 $i$ 个数对答案为 $j$，就满足 $p_i \ne p_j \land p_i \ne q_j \land q_i \ne p_j \land q_i \ne q_j$，首先答案不能是第一组，因为第一组和第三组满足 $p_i = p_1 = p_j$，同理答案也不可能是第二组，那么考虑第三组，因为 $p_i=p_1,q_j=q_1,p_1 \ne q_1$，所以 $p_i \ne q_j$，又因为 $q_1 \ne q_i,q_1=q_j$，所以 $q_i \ne q_j$，同理得 $p_i \ne p_j$，所以第三组中 $j$ 是 $i$ 的答案仅需保证 $q_i \ne p_j$，而 $q_i=p_j$ 的数对只有一个，所以可以直接往下遍历，最多往下遍历 $1$ 次。

那么如果第三组找不到满足条件的数对，就可以去找第四组的，第四组中，答案为 $j$ 也只需要满足 $q_i \ne p_j \land q_i \ne q_j$，就行了，最多有 $1$ 个数对需要全部遍历（第四组只有一个数对除外）。

确定第三组答案同理，可以做到 $\mathcal{O}(n)$。

综上，可以这样构造：
1. 第一组的答案就是第四组中任意 $1$ 个，找不到就是 $-1$。
2. 第四组答案均为 $1$。
3. 第二组每个数对都遍历一次第三组，找不到就遍历第四组，还找不到答案为 $-1$。
4. 第三组同理。


```cpp
#include<vector>

using namespace std; 

const int N = 3e7 + 10;
int ans[N];
vector<int> gp[4];

bool check(int x1, int x2, int x3, int x4){
	if(x1 == x3 || x1 == x4 || x2 == x3 || x2 == x4) return 0;
	return 1;
}

extern "C" int* find_pairs(int n, int m, int u[], int v[]){
	for(int i = 0; i < m; i++) ans[i] = -1;
	for(int i = 0; i < m; i++){
		if(u[i] == u[1] && v[i] == v[1]){
			gp[0].push_back(i);
		}
		else if(u[i] == u[1] || v[i] == u[1]){
			gp[1].push_back(i);
		}
		else if(u[i] == v[1] || v[i] == v[1]){
			gp[2].push_back(i);
		}
		else{
			gp[3].push_back(i);
		}
	}
	if(gp[3].size()) ans[1] = gp[3][0];
	for(int i: gp[3]){
		ans[i] = 1;
	}
	for(int i: gp[1]){
		for(int j: gp[2]){
			if(check(u[i], v[i], u[j], v[j])){
				ans[i] = j;
				break;
			}
		}
		if(ans[i] == -1){
			for(int j: gp[3]){
				if(check(u[i], v[i], u[j], v[j])){
					ans[i] = j;
					break;
				}
			}
		}
	}
	for(int i: gp[2]){
		for(int j: gp[1]){
			if(check(u[i], v[i], u[j], v[j])){
				ans[i] = j;
				break;
			}
		}
		if(ans[i] == -1){
			for(int j: gp[3]){
				if(check(u[i], v[i], u[j], v[j])){
					ans[i] = j;
					break;
				}
			}
		}
	}
	return ans;
}
```

---

