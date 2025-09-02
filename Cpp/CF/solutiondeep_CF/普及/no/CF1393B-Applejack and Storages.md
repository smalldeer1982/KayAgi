# 题目信息

# Applejack and Storages

## 题目描述

你一开始有 $n$ 根木棍，接下来有 $q$ 次操作。

操作如下:
* `+ x` 增加一根长度为 $x$ 的木棍。
* `- x` 减少一根长度为 $x$ 的木棍，保证减少之前有长为 $x$ 的木棍。

你要计算出每次操作之后能否用 $8$ 根木棍拼出一个矩形（可以是正方形）和一个正方形。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 样例 #1

### 输入

```
6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2```

### 输出

```
NO
YES
NO
NO
NO
YES```

# AI分析结果

### 题目内容

你一开始有 $n$ 根木棍，接下来有 $q$ 次操作。

操作如下:
* `+ x` 增加一根长度为 $x$ 的木棍。
* `- x` 减少一根长度为 $x$ 的木棍，保证减少之前有长为 $x$ 的木棍。

你要计算出每次操作之后能否用 $8$ 根木棍拼出一个矩形（可以是正方形）和一个正方形。

### 样例 #1

#### 输入

```
6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2
```

#### 输出

```
NO
YES
NO
NO
NO
YES
```

### 算法分类
模拟

### 题解分析与结论

该题的核心逻辑是通过模拟操作来维护木棍的数量，并判断是否能够拼出一个矩形和一个正方形。主要思路是通过统计木棍长度的出现次数，判断是否存在足够的木棍来满足条件。

#### 题解对比
1. **45dinо** 的题解通过维护 `four` 和 `two` 变量来记录能够组成正方形和矩形的木棍数量，代码简洁且逻辑清晰。评分为4星。
2. **UniGravity** 的题解详细分析了问题的条件，并通过维护 `cnt2` 和 `cnt4` 变量来判断是否满足条件，逻辑严谨。评分为4星。
3. **huayucaiji** 的题解通过贪心策略优先考虑正方形的组成，再判断矩形的组成，思路清晰且代码简洁。评分为4星。

#### 最优关键思路
- 维护 `four` 和 `two` 变量，分别表示能够组成正方形和矩形的木棍数量。
- 每次操作后更新 `four` 和 `two` 的值，并根据条件判断是否能够拼出矩形和正方形。

#### 可拓展之处
- 类似的问题可以通过维护不同数量的变量来判断是否满足特定条件，如拼出多个正方形或矩形。
- 可以扩展到更复杂的图形拼合问题，如拼出多个不同形状的图形。

#### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】线段树 1](https://www.luogu.com.cn/problem/P3384)

### 精选题解

#### 题解1：45dinо (4星)
**关键亮点**：通过维护 `four` 和 `two` 变量，代码简洁且逻辑清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a,four,two,num[100001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		num[a]++;
		if(num[a]%4==0)
			four++;
		if(num[a]%2==0)
			two++;
	}
	scanf("%d",&q);
	while(q--)
	{
		char opt;
		scanf("%s %d",&opt,&a);
		switch(opt)
		{
			case '+':{
				num[a]++;
				if(num[a]%4==0)
					four++;
				if(num[a]%2==0)
					two++; 
				break;
			}
			case '-':{
				num[a]--;
				if(num[a]%4==3)
					four--;
				if(num[a]%2==1)
					two--;
				break;
			}
		}
		if(four&&two>=4)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
```

#### 题解2：UniGravity (4星)
**关键亮点**：详细分析了问题的条件，并通过维护 `cnt2` 和 `cnt4` 变量来判断是否满足条件。
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q;
int a[100005];
int cnt[100005];
int cnt2 = 0, cnt4 = 0; 

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
        
        if (cnt[a[i]] % 4 == 0) cnt4++;
        if (cnt[a[i]] % 2 == 0) cnt2++;
    }
    scanf("%d", &q);
    char s;
    int x;
    while (q--) {
        scanf("%s %d", &s, &x);
        if (s == '+') {
            cnt[x]++;
            
            if (cnt[x] % 4 == 0) cnt4++;
            if (cnt[x] % 2 == 0) cnt2++;
        } else {
            if (cnt[x] % 4 == 0) cnt4--;
            if (cnt[x] % 2 == 0) cnt2--;
            
            cnt[x]--;
        }
        
        if (cnt4 >= 1 && cnt2 >= 4) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```

#### 题解3：huayucaiji (4星)
**关键亮点**：通过贪心策略优先考虑正方形的组成，再判断矩形的组成，思路清晰且代码简洁。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10; 

int n,cnt[maxn],m,four,two;
char ch;

signed main() {
	n=read();
	for(int i=1;i<=n;i++) {
		int x=read();
		cnt[x]++;
		if(cnt[x]%4==0) {
			four++;
			two--;
		}
		if(cnt[x]%4==2) {
			two++;
		}
	}
	m=read();
	
	for(int i=1;i<=m;i++) {
		cin>>ch;
		int x=read();
		if(ch=='+') {
			cnt[x]++;
			if(cnt[x]%4==0) {
				four++;
				two--;
			}
			if(cnt[x]%4==2) {
				two++;
			}
		}
		else {
			if(cnt[x]%4==0) {
				four--;
				two++;
			}
			if(cnt[x]%4==2) {
				two--;
			}
			cnt[x]--;
		}
		
		if(four>0&&two>1) {
			printf("Yes\n");
		}
		else if(four>1) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---
处理用时：45.50秒