# Yet Another Palindrome Problem

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Your task is to determine if $ a $ has some subsequence of length at least $ 3 $ that is a palindrome.

Recall that an array $ b $ is called a subsequence of the array $ a $ if $ b $ can be obtained by removing some (possibly, zero) elements from $ a $ (not necessarily consecutive) without changing the order of remaining elements. For example, $ [2] $ , $ [1, 2, 1, 3] $ and $ [2, 3] $ are subsequences of $ [1, 2, 1, 3] $ , but $ [1, 1, 2] $ and $ [4] $ are not.

Also, recall that a palindrome is an array that reads the same backward as forward. In other words, the array $ a $ of length $ n $ is the palindrome if $ a_i = a_{n - i - 1} $ for all $ i $ from $ 1 $ to $ n $ . For example, arrays $ [1234] $ , $ [1, 2, 1] $ , $ [1, 3, 2, 2, 3, 1] $ and $ [10, 100, 10] $ are palindromes, but arrays $ [1, 2] $ and $ [1, 2, 3, 1] $ are not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, the array $ a $ has a subsequence $ [1, 2, 1] $ which is a palindrome.

In the second test case of the example, the array $ a $ has two subsequences of length $ 3 $ which are palindromes: $ [2, 3, 2] $ and $ [2, 2, 2] $ .

In the third test case of the example, the array $ a $ has no subsequences of length at least $ 3 $ which are palindromes.

In the fourth test case of the example, the array $ a $ has one subsequence of length $ 4 $ which is a palindrome: $ [1, 2, 2, 1] $ (and has two subsequences of length $ 3 $ which are palindromes: both are $ [1, 2, 1] $ ).

In the fifth test case of the example, the array $ a $ has no subsequences of length at least $ 3 $ which are palindromes.

## 样例 #1

### 输入

```
5
3
1 2 1
5
1 2 2 3 2
3
1 1 2
4
1 2 2 1
10
1 1 2 2 3 3 4 4 5 5```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：tuzhewen (赞：2)

### 题目大意：
看一个数组里面有没有一个长度大于$3$的回文**子序列**

### 思路：
既然是子序列，那么就不要求连续，所以说我们只要看一个数在不连续的情况下出现了两次及以上或者出现了三次及以上。

举个栗子：``1 2 3 1 4``

我们发现$1$出现了两次，那么我们就有$2$个答案：``1 2 1`` 和 ``1 3 1``

------

但是如果是这样：``1 1 2 3 3``

我们发现虽然$1,3$都出现了两次，但是并没有回稳子序列，因为出现的两次是连续的，中间没有“夹住”任何数字，所以没有解。

------

再来看：
``1 1 1 2 3``

尽管所有$1$是连续的，但是``1 1 1``就是我们所想要的答案。

好了，思路讲完了，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[5005];
int vis1[5005],vis2[5005];//作用如上文（具体看下文）
int main() {
	scanf("%d",&t);
    while(t--) {
        scanf("%d",&n);
        memset(vis1,0,sizeof(vis1));
        memset(vis2,0,sizeof(vis2));//不要忘记初始化！
        for(int i=1;i<=n;i++) {
            scanf("%d",&a[i]);
            vis1[a[i]]++;//计算每一个数字出现了多少次
            if(a[i]!=a[i-1]) vis2[a[i]]++;//计算不连续的数字出现了多少次
        }
        bool flag=false;//判断答案
        for(int i=1;i<=n;i++) {
            if(vis2[a[i]]>=2||vis1[a[i]]>=3) {
                flag=true;//如果有解就直接退出循环
                break;
            }
        }
        if(!flag) puts("NO");
        else puts("YES");
    }
	return 0;
}
```

---

## 作者：do_while_false (赞：2)

【题目大意】

给定 $t$ 个长度为 $n$ 的序列，问是否存在一个长度至少为 $3$ 的子序列是回文的。

【解题思路】

因为 $a_i<n$，我们可以想到这种思路：创造 $n$ 个桶，如果 $a_i \neq a_i-1$ ，就将读入的数放入桶中，此时如果某个桶的大小达到了 $2$，就说明有两个不相邻的元素相等，可以得到此时至少有一个长度为 $3$ 的回文子序列。（我们要先把 $a_1$ 所在的桶的值加 $1$，循环从 $2$ 开始）

【代码】

```cpp
#include<bits/stdc++.h>
#define MAXN 5000 + 10
using namespace std;
int t,n,a[MAXN],ton[MAXN];
bool flag=false;
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	t=read();
	while(t--) {
		n=read();
		flag=false;
		memset(a,0,sizeof(a));
		memset(ton,0,sizeof(ton));//初始化 
		for(int i=1;i<=n;i++) a[i]=read();//读入 
		ton[a[1]]++;//预处理 
		for(int i=2;i<=n;i++) 
			if(a[i]!=a[i-1]) //判断是否符合条件 
				ton[a[i]]++;//加桶的值 
		for(int i=1;i<=n;i++) if(ton[i]>=2) flag=true;//判断是否存在长度至少为3的回文子序列 
		if(flag==true) printf("YES\n");
		else printf("NO\n");//输出 
	}
	return 0;
}

```

---

## 作者：Ryo_Yamada (赞：2)

### 题目翻译

没人翻找百度

给 $t$ 个长为 $n(n \leq 5000)$的数组，问是否存在一个长度至少为3的子序列是回文的。

### 思路

前言：借鉴了zhugezy巨佬的思路。

我们考虑：回文串可以从左右同时删除一个数，这样还是一个回文串。因此原题等价于判断是否存在一个长度大于等于3的回文子序列。

直接$O(tn^2)$暴力即可。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[5005], b[5005];
bool check() {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            if (b[a[j]])
                return true;
        b[a[i]] = 1;
    }
    return false;
}
int main() {
    cin >> t;
    while (t--) {
        memset(b, 0, sizeof(b));
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        cout << (check() ? "YES\n" : "NO\n");
    }
    return 0;
}
```


---

## 作者：Ignotus (赞：1)

### 题目大意  
本题其实就是问你一个数组 $a$ 中是否有一个长度大于等于 $3$ 的回文子序列。**注意：题目要求不一定连续。**   
因为题目要求长度为 $3$ 即可，所以其实只需要检查一个数在数组 $a$ 中是否不连续出现两次，$O(n)$ 即可解决。   
定义 $pos$ 数组存每个数第一次出现的位置。  
Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int a[5010],pos[5010],T,n,flag;
  
int main()
{
    cin>>T;
    while(T--){
        flag=0;
        memset(pos, 0, sizeof pos);
        scanf("%d",&n);
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        for(int i=1; i<=n; i++){
            if(!pos[a[i]]) pos[a[i]]=i;//如果没有出现，则记录第一次出现的位置
            else{
            	if(i-pos[a[i]]>1){
                    flag=1;
                    break;
                }
            }//否则，如果出现过，且不与第一次出现相连，则再取中间任意一个数即可满足长度为3的回文子序列
        }
        if(flag) puts("YES");
        else puts("NO");//如果遍历了所有a[i]且不满足条件，输出"NO"
    }
    return 0;
}
```


---

## 作者：registerGen (赞：1)

首先只需考虑 $3$ 个的情况的就可以了，因为有 $3$ 个就一定有 $4$ 个以上个。

设这个三元子序列为 $\{a_i,a_j,a_k\}$，不妨设 $i<j<k$，则有 $a_i=a_k$。

于是我们只需找到两个相等的，且距离 $>1$ 的数。若找得到，则输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

---

下面放出代码，时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int N=5000;

int n,a[N+10],h[N+10];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(h,0,sizeof(h));
		scanf("%d",&n);
		int tmp=0;
		bool ok=false;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			h[x]++;
			if(h[x]>=2&&x!=tmp)ok=true;
			tmp=x;
		}
		if(ok)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

**Upd on 2020/3/13**

然而，这份代码被 hack 了！

hack 数据：

```plain
1
3
1 1 1
```

std：`YES`；this：`NO`。

于是，我们得出一个结论：

当一个数的出现次数 $\ge 3$ 时，答案仍然为 $\texttt{YES}$。

---

AC 代码：（话说这道题的 hack 数据好多啊qwq）

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int N=5000;

int n,a[N+10],h[N+10]; // h[i] 表示 i 的出现次数。

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(h,0,sizeof(h));
		scanf("%d",&n);
		int tmp=0;
		bool ok=false;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			h[x]++;
			if(h[x]==2&&x!=tmp)ok=true;
			if(h[x]>=3)ok=true;
			tmp=x;
		}
		if(ok)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：1)

题目传送门:[CF](https://codeforces.com/problemset/problem/1324/B) [洛谷](https://www.luogu.com.cn/problem/CF1324B)

### 题目翻译

给定有n个数的序列，询问这个序列有没有 长度$\geqslant 3$ 的回文子序列。

这里的子序列可以在原序列中不连续，但是必须保持在原序列中相对的顺序。

这里的回文序列即对于一个序列a，保证$a_i=a_{n-i-1} (0\leqslant i\leqslant n)$的序列

#### 输入格式

第一行一个整数T，代表有T组数据

对于每一组数据

第一行一个整数n，代表序列长度

第二行 n 个整数，代表序列

#### 输出格式

T行，如果有长度$\geqslant 3$的回文子序列，则输出"YES"，否则输出"NO"

### 题目分析

首先如果我们有长度$\geqslant 4$的序列，我们一定可以选出3个数来构成长度$=3$的序列，所以我们只需要判断有没有长度$=3$的回文子序列即可

对于一个长度$=3$的序列，显然左右两端的字母一定相同(根据定义得出)，而中间一个可以随便选。所以我们只要找出两个相同字母，再随便从中间找一个字母就可以构成一个满足条件的回文子序列

### Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,T,a[5001],vis[5001];
bool f;
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		f=0;//f为0时无解，为1时有解 
		for(int i=1;i<=n;i++)
			vis[i]=0;//初始化为0
		//vis[i]代表数字i第一次出现的位置 
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(!vis[a[i]]) vis[a[i]]=i;
			//如果之前没出现过，就记录下第一次出现的位置 
			else if(i-vis[a[i]]>1) f=1;
			//如果他们之间有数，就说明能构成一个回文子序列 
		}
		if(f) puts("YES");
		else puts("NO");
	}
	return 0;
}
```



---

## 作者：__OwO__ (赞：0)

看别的题解都是$O(tn^2)$的,发布一篇$O(tn)$的题解

我们发现这道题数列中只要有两个相同的并且间隔超过一个的数字就有回文子串

所以我们给每个数字计出现次数

如果出现上述情况就是回文串

这里用每个的贡献值来使枚举更方便

上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,*arr,*num;
		cin>>n;
		arr=new int[n];
		num=new int[n+10];
		memset(num,0,sizeof(int)*(n+10));
		cin>>arr[0];
		num[arr[0]]++;
		int yes=0;
		for(int i=1;i<n;i++){
			cin>>arr[i];
			if(arr[i]!=arr[i-1]&&num[arr[i]]!=0)
				num[arr[i]]+=2;
			else
				num[arr[i]]++;
		}
		for(int i=0;i<n+10;i++){
			if(num[i]>=3){
				yes=1;
				break;
			}
		}
		if(yes)cout<<"YES\n";
		else cout<<"NO\n";
	}
}
```

---

