# Complementary XOR

## 题目描述

You have two binary strings $ a $ and $ b $ of length $ n $ . You would like to make all the elements of both strings equal to $ 0 $ . Unfortunately, you can modify the contents of these strings using only the following operation:

- You choose two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ );
- For every $ i $ that respects $ l \le i \le r $ , change $ a_i $ to the opposite. That is, $ a_i := 1 - a_i $ ;
- For every $ i $ that respects either $ 1 \le i < l $ or $ r < i \le n $ , change $ b_i $ to the opposite. That is, $ b_i := 1 - b_i $ .

Your task is to determine if this is possible, and if it is, to find such an appropriate chain of operations. The number of operations should not exceed $ n + 5 $ . It can be proven that if such chain of operations exists, one exists with at most $ n + 5 $ operations.

## 说明/提示

In the first test case, we can perform one operation with $ l = 2 $ and $ r = 2 $ . So $ a_2 := 1 - 1 = 0 $ and string $ a $ became equal to 000. $ b_1 := 1 - 1 = 0 $ , $ b_3 := 1 - 1 = 0 $ and string $ b $ became equal to 000.

In the second and in the third test cases, it can be proven that it's impossible to make all elements of both strings equal to $ 0 $ .

In the fourth test case, we can perform an operation with $ l = 1 $ and $ r = 2 $ , then string $ a $ became equal to 01, and string $ b $ doesn't change. Then we perform an operation with $ l = 2 $ and $ r = 2 $ , then $ a_2 := 1 - 1 = 0 $ and $ b_1 = 1 - 1 = 0 $ . So both of string $ a $ and $ b $ became equal to 00.

In the fifth test case, we can perform an operation with $ l = 1 $ and $ r = 1 $ . Then string $ a $ became equal to 011 and string $ b $ became equal to 100. Then we can perform an operation with $ l = 2 $ and $ r = 3 $ , so both of string $ a $ and $ b $ became equal to 000.

## 样例 #1

### 输入

```
5
3
010
101
2
11
10
4
1000
0011
2
10
10
3
111
111```

### 输出

```
YES
1
2 2
NO
NO
YES
2
1 2
2 2
YES
2
1 1
2 3```

# 题解

## 作者：RNTBW (赞：8)

### 序
1750，一个很好的数字捏。
## 题意
给定两个长度相同的 01 串 $a,b$。

每次操作可以选中两个下标 $l,r$，$\forall i \in[l,r],a_i=1-a_i$，同时 $\forall i\in[1,l-1]$ 或 $[r+1,n],b_i=1-b_i$。
## 思路

_像这种 $n$ 很大且又是求操作方案的题，一般都有特定的操作方法，绝对不是乱操作。_

—— 沃·兹基硕德

先来判断。

上结论：如果两个串之间的每个字符既不全部相同，又不全部相异，则无解。

考虑证明。

我们先假设最简单的一种情况：只有一组 $x,y$ 满足 $\forall i \in[x,y],a_i=b_i$，且 $1<x\leq y<n$，$x,y$ 外的 $i$ 全都满足 $a_i=1-b_i$。

那么我们选的 $l,r$ 就有三种情况：

1. 选中的 $[l,r]$ 与 $[x,y]$ 无交集

这种情况下，$[x,y]$ 外的 $a_i=b_i$，而 $[x,y]$ 内的 $a_i=1-b_i$。

2. 选中的 $[l,r]$ 与 $[x,y]$ 部分交集

这种情况下，$[l,r]$ 内与 $[x,y]$ 无交集的部分的 $a_i=b_i$，$[x,y]$ 内的 $a_i=1-b_i$。

3. 选中的 $[l,r]$ 被 $[x,y]$ 包含。

这种情况下，$[x,y]$ 内的 $a_i=1-b_i$，$[x,y]$ 外的 $a_i=b_i$。

4. 选中的 $[l,r]$ 包含 $[x,y]$。

仍会出现一些 $a_i=b_i$，另一些 $a_i=1-b_i$ 的情况，读者自证不难。

所以，无论怎么选择，总会陷入死循环。

那么结论得证。

所以我们的“特定的操作方法”是什么呢？

我们可以先不管 $b$ 串，将 $a$ 串中的 1 全部修改成 0。

模拟可知：

- 当 $a,b$ 相同且操作次数（即 $a$ 中 1 的个数）为奇数时，最后 $a=00000....$
，$b=11111....$。

- 当 $a,b$ 全部相异，且操作次数为偶数的时候，也是 $a=00000....$，$b=11111....$。

其他情况下直接就可以将 $a,b$ 置零。

那么上述情况就需要用到我~~乱搞出来~~的特定解题方法：

```cpp
1 n//a 串全部置1
1 1
2 n//奇妙乱搞
```

至此，本题解决。

## 正确代码
```cpp#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001];
int t,n,i,k,s;
bool f,g,h;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);k=s=f=g=h=0;
		for(i=1;i<=n;i++) scanf("%1d",&a[i]);
		for(i=1;i<=n;i++)
		{
			scanf("%1d",&b[i]);
			if(a[i]==b[i])f=1;
			else g=1;
		}
		if(f&&g)//判断
		{puts("NO");continue;
		}
		puts("YES");
		for(i=1;i<=n;i++)
			if(a[i])k++;
		s=k;
		if((f&&(k%2)) || (g&&(k%2==0)))s+=3,h=1;//此时多了3步操作，具体见上
		printf("%d\n",s);
		for(i=1;i<=n;i++)
			if(a[i])printf("%d %d\n",i,i);//先将a置零
		if(h)printf("1 %d\n1 1\n2 %d\n",n,n); 
	}
	return 0;
}
```

---

## 作者：ningago (赞：1)

由于异或有性质：$a\oplus 1\oplus 1=a$。

所以我们可以把操作化简为：

$\forall i\in [l,r],a_i \oplus 1,b_i \oplus 1$，并且随后 $\forall i \in [1,n],b_i\oplus 1$（也就是全局取反一次）。

所以我们得知了一个显然的结论：如果答案为 `YES`，那么初始时 $a$ 数组与 $b$ 数组要么全部不同，要么一模一样。

然后我们可以把先所有 $a_i=1$ 的 $i$ 进行一次 `i i` 的操作。

随后出现的局面有两种情况：

- $a$ 为 `00000`，$b$ 为 `00000`。

这样就万事大吉，直接润。

- $a$ 为 `00000`，$b$ 为 `11111`。

也就是我们需要通过奇数次操作，使得 $a$ 不变。

这时执行以下操作即可：

```
1 1
2 2
1 2
```

代码：

```cpp
#include <cstdio>
#include <cstring>

#define N 200010
int T;
int n;
char a[N],b[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%s%s",a + 1,b + 1);
		bool flag1 = 1,flag2 = 1;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] != b[i])
				flag1 = 0;
			else
				flag2 = 0;
		}
		if(!flag1 && !flag2)
		{
			printf("NO\n");
			continue;
		}
		int t = 0;
		if(flag1)
			t = 1;
		int cnt = 0;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] == '1')
				cnt++;
		}
		if(t)
		{
			if(cnt % 2 == 0)
			{
				printf("YES\n%d\n",cnt);
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
			else
			{
				printf("YES\n%d\n",cnt + 3);
				printf("1 1\n2 2\n1 2\n");
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
		}
		else
		{
			if(cnt % 2 == 1)
			{
				printf("YES\n%d\n",cnt);
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
			else
			{
				printf("YES\n%d\n",cnt + 3);
				printf("1 1\n2 2\n1 2\n");
				for(int i = 1;i <= n;i++)
					if(a[i] == '1')
						printf("%d %d\n",i,i);
				continue;
			}
		}
	}
	return 0;
}
```

---

## 作者：JiuZhE66666 (赞：0)

# 题解

观察发现，操作和异或很像，令 $c=a\oplus b$，则每一次操作都会令 $c$ 异或上 $111...111$。

因此，存在构造方法的前提是 $a\oplus b = 111...111$ 或者 $a\oplus b =000...000$

如果 $a\oplus b =000...000$，

则我们可以通过奇数次操作让 $a$ 变成 $111...111$ 然后再整体操作一下；或者通过偶数次操作让 $a$ 变成 $000...000$，那么此时 $b$ 一定也是 $000...000$。

如果 $a\oplus b =111...111$，

则我们可以通过偶数次操作让 $a$ 变成 $111...111$ 然后再整体操作一下；或者通过奇数次操作让 $a$ 变成 $000...000$，那么此时 $b$ 一定也是 $000...000$。

---

## 作者：Micnation_AFO (赞：0)

不一样的做法：贪心 + 线段树。

------------

首先我们可以发现，下面这样的例子是不行的：

```
000
100
```

```
000 
001
```

但是下面这两个例子是可行的：
```
000
000
```

```
000
111
```

也就是说，当第一行全部是 $0$ 的时候，第二行要么全是 $1$，要么全是 $0$，否则就输出 `NO`。

那么就可以依次对第一行的每个 $1$ 进行操作，然后线段树维护**第二行的**区间和，支持区间异或操作，按照题目模拟即可。

第一行全变成 $0$ 之后，之前看第二行所有数的和是不是 $0$ 或者 $n$，如果不是直接输出 `NO`。如果和为 $0$，那么方案就是把第一行的一全部输出。

如果和为 $1$，那么除了把第一行一的位置全部输出一遍以外，还需要把第二行全部翻一下。我们随便把第二行划分为两个区间，每个区间分别操作一次，然后整体操作一次，就可以了。不过这里要注意特判 $n$ 为 $1$ 的情况。

$\texttt{AC}$ 代码：

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 200010;

int T;
string a, b;
vector<int> v;

struct SegmentTree {
    int l, r;
    int dat;
    bool flag;
} t[N << 2];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].dat = b[l] - '0', t[p].flag = false; return; }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build((p << 1) | 1, mid + 1, r);
    t[p].dat = t[p << 1].dat + t[(p << 1) | 1].dat, t[p].flag = false;
}

void spread(int p) {
    if (t[p].flag) {
        t[p << 1].dat = t[p << 1].r - t[p << 1].l + 1 - t[p << 1].dat;
        t[(p << 1) | 1].dat = t[(p << 1) | 1].r - t[(p << 1) | 1].l + 1 - t[(p << 1) | 1].dat;
        t[p << 1].flag = !t[p << 1].flag, t[(p << 1) | 1].flag = !t[(p << 1) | 1].flag;
        t[p].flag = false;
    }
}

void change(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].dat = t[p].r - t[p].l + 1 - t[p].dat;
        t[p].flag = !t[p].flag;
        return;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r);
    if (r > mid) change((p << 1) | 1, l, r);
    t[p].dat = t[p << 1].dat + t[(p << 1) | 1].dat;
}

int main() {
    cin >> T;
    while (T--) {
        int n; cin >> n >> a >> b;
        v.clear(); a = " " + a, b = " " + b;
        build(1, 1, n);
        for (int i = 1; i <= n; i++)
            if (a[i] == '1') v.push_back(i);
        for (auto it : v) {
            if (it != 1) change(1, 1, it - 1);
            if (it != n) change(1, it + 1, n);
        }
        if ((t[1].dat != n && t[1].dat) || (n == 1 && t[1].dat)) { puts("NO"); continue; }
        puts("YES");
        int len = !t[1].dat ? v.size() : v.size() + 3;
        cout << len << "\n";
        for (auto it : v) cout << it << " " << it << "\n";
        if (t[1].dat) {
            cout << 1 << " " << 1 << "\n";
            cout << 2 << " " << n << "\n";
            cout << 1 << " " << n << "\n";
        }
    }
    return 0;
}
```

---

## 作者：wanghaoran00 (赞：0)

### 题意
给定两个字符串 $a,b$ 通过将 $a$ 中 $[l,r]$ 取反（即零变一，一变零），$b$ 中其他值取反，使所有值变为零。

### 思路
如果两序列中同时出现上下相同和上下不同的情况，易知不行，在上下完全相同时将 $a$ 中的一变成零（零变成一也可以），若操作次数为奇数最后 $a$ 序列全是 $0$ 偶数次则最后全是 $1$，$l=1,r=n$ 变换即可。（见代码）

AC code
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,x0,x1,ans,b1,b0,maxb0,maxb1;
string s1,s2;
int main(){
    scanf("%d",&t);
    while(t--){
        b0=0,b1=0,x0=0,x1=0,ans=0;
        scanf("%lld",&n);
        cin>>s1>>s2;
        for(int i=0;i<n;i++){
            if(s1[i]=='0'){//0的个数
                x0++;
            }
            if(s1[i]=='1'){//1的个数
                x1++;
            }
            if(s1[i]==s2[i]){上下相同
                b0=1;
            }
            else{//上下不同
                b1=1;
            }
        }
        if(b0==1&&b1==1){如果两种情况同时存在无法变换
            printf("NO\n");
        }
        else{
            printf("YES\n");
            if(b0==1){
                //cout<<"相同";
                if(x0==n||x1==n){
                    if(x0==n){//无需变换
                       printf("0\n");
                    }
                    else{//集体变换一次即可
                        printf("2\n1 1\n2 %d\n",n);
                    }
                }
                else{
                    for(int i=0;i<n;i++){
                        if(s1[i]=='1'){//将1前变换，若偶数次则a全为0，反之为1
                            ans++;
                        }
                    }
                    if(x1%2==0){
                        printf("%d\n",ans);
                        for(int i=0;i<n;i++){
                            if(s1[i]=='1'){
                                printf("%d %d\n",i+1,i+1);
                            }
                        }
                    }
                    else{//3是模拟上方的三次操作
                        printf("%d\n",ans+3);
                        for(int i=0;i<n;i++){
                            if(s1[i]=='1'){
                                printf("%d %d\n",i+1,i+1);
                            }
                        }
                        printf("1 %d\n",n);
                        printf("1 1\n2 %d\n",n);
                    }
                }
            }
            else{//不同与上方相反
                for(int i=0;i<n;i++){
                    if(s1[i]=='1'){
                        ans++;
                    }
                }
                if(x1%2==1){
                    printf("%d\n",ans);
                    for(int i=0;i<n;i++){
                        if(s1[i]=='1'){
                            printf("%d %d\n",i+1,i+1);
                        }
                    }
                }
                else{//正好在n+4为上限时达成目标
                    printf("%d\n",ans+3);
                    for(int i=0;i<n;i++){
                        if(s1[i]=='1'){
                            printf("%d %d\n",i+1,i+1);
                        }
                    }
                    printf("1 %d\n",n);
                    printf("1 1\n2 %d\n",n);
                }
            }
        }
    }
	return 0;
}

```

---

