# Paint the Digits

## 题目描述

You are given a sequence of $ n $ digits $ d_1d_2 \dots d_{n} $ . You need to paint all the digits in two colors so that:

- each digit is painted either in the color $ 1 $ or in the color $ 2 $ ;
- if you write in a row from left to right all the digits painted in the color $ 1 $ , and then after them all the digits painted in the color $ 2 $ , then the resulting sequence of $ n $ digits will be non-decreasing (that is, each next digit will be greater than or equal to the previous digit).

For example, for the sequence $ d=914 $ the only valid coloring is $ 211 $ (paint in the color $ 1 $ two last digits, paint in the color $ 2 $ the first digit). But $ 122 $ is not a valid coloring ( $ 9 $ concatenated with $ 14 $ is not a non-decreasing sequence).

It is allowed that either of the two colors is not used at all. Digits painted in the same color are not required to have consecutive positions.

Find any of the valid ways to paint the given sequence of digits or determine that it is impossible to do.

## 说明/提示

In the first test case, $ d=040425524644 $ . The output $ t=121212211211 $ is correct because $ 0022444 $ (painted in $ 1 $ ) concatenated with $ 44556 $ (painted in $ 2 $ ) is $ 002244444556 $ which is a sorted sequence of $ n $ given digits.

## 样例 #1

### 输入

```
5
12
040425524644
1
0
9
123456789
2
98
3
987
```

### 输出

```
121212211211
1
222222222
21
-
```

# 题解

## 作者：jiangXxin (赞：7)

这道题，当时差点没有做出来.

其实这道题就是想让你求出两个子序列，当这两个子序列连接起来，是一个不下降子序列.

思路：用两个数组，一个记录输入的数据，另外一个进行复制，并排序.
显然，我们想要两个子序列拼起来不下降，那么我们就可以将原来的与排完序的进行比较，如果相同，则把它们分成第一组，否则分成第二组。

**无解的判断**:我们像刚才那样，已经获得了一个序列，判断它能不能满足不下降序列就OK了。

那么代码如下：
```cpp
    /**
    *    author:  a2954898606
    *    created: 2019/09/14 22:37:02
    **/
    #include<bits/stdc++.h>
    #define REP(A,B,I) for(int I=(A);I<=(B);I++)
    #define PER(A,B,I) for(int I=(A);I>=(B);I--)
    #define max(X,Y) ((X)<(Y)?(Y):(X))
    #define min(Y,X) ((X)<(Y)?(X):(Y))
    #define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
    #define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
    #define LL long long
    #define N 258401
    using namespace std;
    int t,n;
    int a[N],b[N],c[N],ans[N];
    char s[N];
    int main(){
        //read(1)
        //write(1)
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
     
        cin>>t;
        while(t--){
            cin>>n;
            cin>>(s+1);
            REP(1,n,i){
                a[i]=s[i]-'0';
                b[i]=a[i];
            }
            sort(b+1,b+n+1);
            int pos=1;
            REP(1,n,i){
                if(a[i]==b[pos]){
                    pos++;
                    ans[i]=1;
                }
                else ans[i]=2;
            }
            int tim=0;
            REP(1,n,i){
                if(ans[i]==1)c[++tim]=a[i];
            }
            REP(1,n,i){
                if(ans[i]==2)c[++tim]=a[i];
            }//获得一个答案序列
            int flag=0;
            REP(1,n-1,i){
                if(c[i]>c[i+1]){//无解的判断
                    flag=1;
                    break;
                }
            }
            if(flag){
                cout<<"-"<<endl;
                continue;
            }
            REP(1,n,i){
                cout<<ans[i];
            }
            cout<<endl;
        }
        return 0;
    }
```


---

## 作者：wuyixiang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1209C)

题目大意：一个字符串分成两个子序列，问能不能有一种分割方案使得第二个子序列接在第一个子序列之后使得这个序列单调不降，并输出分割方式。

思路：排序+贪心

我们会发现一个规律：前面若干个数字都在第一个子序列，后面若干个数字都在第二个子序列。偶尔中间可能会有一个数字，它可能在两个子序列中出现。我们可以直接枚举第一个子序列最后面的下标，如果某个字符接不下了，则换一个子序列继续存。当如果两个子序列也不够用了的话，直接跳出并输出 `-` 即可。

## AC CODE:

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int t,n,b[11][200001],c[200001];
int main()
{
    string s,u;
    cin >> t;
    while(t --)
    {
        cin >> n >> s;
        int cnt = 0,r = 1,d[200001] = {};
        memset(c,0,sizeof(c));
        for(int i = 0;i < n;i ++)b[s[i] - 48][++c[s[i] - 48]] = i;
        for(int i = 0;i <= 9;i ++)sort(b[i] + 1,b[i] + c[i] + 1);
        for(int i = 0;i <= 9;i ++){
        	int w = 0,w2 = 0;
            for(int j = 1;j <= c[i];j ++)
            {
                if(cnt > b[i][j])w = 1;//接不上的情况
                if(w == 1 && r == 2)//跳出
                { 
                	r = 200;
                	break;
				}
                if(w == 1 && cnt <= b[i][j])//虽然第一个前面接不上，但是后面可以存
				{
					if(w2 == 0)w2 = 1,cnt = b[i][j - 1];
					d[b[i][j]] = r;
				}
                if(w == 1 && w2 == 0)d[b[i][j]] = r + 1;
                else if(w == 0 && w2 == 0)cnt = b[i][j],d[b[i][j]] = r;
            }
            if(r == 200)break;
            if(w == 1)r ++;//换子序列
            if(w2 == 0 && w == 1)cnt = b[i][c[i]];//如果接了一部分，就从最后字符的下标开始

        }
        if(r > 2)cout << "-\n";//2个子序列存不下，输出-
        else
        {
        	for(int i = 0;i < n;i ++)cout << d[i];
        	cout << '\n';
		}
    }
}
```


---

## 作者：叶ID (赞：3)

题目：[CF1209C Paint the Digits](https://www.luogu.org/problem/CF1209C)

---

### 题意简述

给出一个序列（数值为0到9，即一个数字位），要求将其分成两个子序列，并首尾相接成一个不下降序列。输出任意一组可行解。

输出格式：输出一行长度为原序列长度的，1和2构成的数字串。如果第$i$个元素分到子序列$1$（放在前面的那个），第$i$位是$1$，否则是$2$

---

### 解题思路

我们注意到序列元素很小，可以枚举序列$1$和序列$2$的分界值$t$。

那么显然序列$1$的所有元素不大于$t$，且是不下降序列。序列$2$的所有元素不小于$t$，且是不下降序列。

我们从后往前扫描（模拟一下会发现从后往前才能对）确定出子序列$1$。具体地，维护一个$min$值，初始化为$10$。从后向前扫描原序列，对于每一个不大于$t$的值：

- 如果这个值不大于$min$，将这个值加入序列$1$，并更新$min$为这个值
- 否则
  - 如果这个值小于$t$，显然它也不可能出现在序列$2$中，无解。
  - 如果这个值等于$t$，它可以出现在序列$2$中，暂时不将其放入序列$1$
  
操作完成后，就剩下的元素就构成了序列$2$，此时判断序列2是否不下降就可以了。

### 代码

```cpp
// status: [Accepted]
// oj:     [Codeforces]
 
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 200001;
int arr[MAXN];
int n;
int col[MAXN];
 
int main() {
    ios::sync_with_stdio(false);
    
    int T;
    cin>>T;
 
    while(T--) {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) {
            char c;
            cin>>c;
            arr[i] = c-'0';
        }
 
        bool solved = false;
        for(int t=0;t<10;t++) {
            int m1 = 10;
            int m2 = 10;
            bool ok = 1;
            for(int i=1;i<=n;i++) col[i]=-1;
            for(int i=n;i>=1;i--) {
                if(arr[i]<=t) {
                    if(arr[i]<=m1) col[i] = 1;
                    if(arr[i]>m1 && arr[i]!=t) {ok=0;break;}
                    if(arr[i]<=m1) m1=arr[i];
                    // if(t==4) cerr<<"Colored "<<i<<'>'<<arr[i]<<" 1"<<endl;
                }
            }
            for(int i=n;i>=1;i--) {
                if(arr[i]>=t && col[i]!=1) {
                    col[i] = 2;
                    if(arr[i]>m2) {ok=0;break;}
                    m2=arr[i];
                }
            }
            if(ok) {
                for(int j=1;j<=n;j++) {
                    cout<<col[j];
                }
                cout<<'\n';
                solved = 1;
                break;
            }
        }
 
        if(!solved) {
            cout<<'-'<<'\n';
        }
    }
}
```


---

## 作者：皎月半洒花 (赞：2)

一开始猜了一个把 LIS 找出来就完了。然后发现假的离谱。然后就考虑观察性质，发现如果存在合法答案，那么对于一个 $i$ 如果位置不变，会有 $1\sim i-1$ 都 $\leqslant i$ 。不难发现这是个十分强的必要条件。于是可以这么把答案取出来，然后去 check 一下充分性就好了。复杂度线性。

```cpp
#include <cstdio>
 
#include <vector>
 
#include <cstring>
 
#include <algorithm>
 
const int N = 301000 ;
 
using namespace std ;
 
int n, T ;
int maxc ;
int maxv ;
int res[N] ;
int ans[N] ;
int base[N] ;
bool vis[N] ;
vector <int> ans1, ans2 ;
 
int main(){
    scanf("%d", &T) ;
    while (T --){
        scanf("%d", &n) ;
        maxv = maxc = 0 ;
        ans2.clear() ; ans1.clear() ;
        memset(vis, 0, sizeof(vis)) ;
        for (int i = 1 ; i <= n ; ++ i)
            scanf("%1d", &base[i]) ;
        for (int i = 1 ; i <= n ; ++ i)
            if (maxv > base[i])
                 vis[i] = 1, maxc = max(base[i], maxc) ;
            else maxv = std :: max(maxv, base[i]) ;
        for (int i = 1 ; i <= n ; ++ i){
            if (vis[i] || base[i] < maxc)
                 ans1.push_back(i) ;
            else ans2.push_back(i) ;
        }
        int cnt = 0 ;
        for (auto k : ans1) ans[k] = 1, res[++ cnt] = base[k] ;
        for (auto k : ans2) ans[k] = 2, res[++ cnt] = base[k] ;
       // for (int i = 1 ; i <= n ; ++ i) printf("%d ", res[i]) ; puts("") ;
        for (int i = 1 ; i <= n ; ++ i)
            if (res[i] < res[i - 1]) goto cc ;
        for (int i = 1 ; i <= n ; ++ i)
            printf("%d", ans[i]) ; puts("") ; continue ;
        cc : puts("-") ;
    }
}
```

# 

---

## 作者：E1_de5truct0r (赞：1)

## 思路

最终的顺序一定是和把原数组排序之后的顺序一致的。

所以我们就把原数组存一个副本并排序，按照副本的顺序依次向后找，选出所有的 1 即可。这个是双指针的基础应用，可以 $O(n)$ 做到。最后的判断很简单，看一下剩下的没有选出来的 2 是不是按顺序排列的即可。

因为我们是按最小值选的，所以 2 的开头一定大于等于 1 的末尾，这个正确性是无需判断的。

总时间复杂度 = 排序 + 查找 = $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[200005],b[200005];
int col[200005];
vector<char> F;
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n; scanf("%d%s",&n,a+1);
		for(int i=1;i<=n;i++) b[i]=a[i]; // 副本
		sort(b+1,b+1+n); // 排序
		int j=1;
		for(int i=1;i<=n;i++)
			if(a[i]==b[j]) j++,col[i]=1;
			else col[i]=2,F.push_back(a[i]); // 基础的双指针查找
		bool flag=1;
		for(int i=1;i<F.size();i++)
			if(F[i]<F[i-1]) // 判断一下剩下的是不是按升序排列
			{
				flag=0;
				break;
			}
		if(!flag) putchar('-');
		else
			for(int i=1;i<=n;i++)
				printf("%d",col[i]); //输出
		putchar('\n');
		F.clear(); /*记得清空 qwq
	}
	return 0;
}
```

## 等等，先别走——


当然，本题也有 $O(n)$ 做法：预处理一个 $minn$ 数组，$minn_i = \min\limits_{j=i}^n a_j$。每次查找的时候就判断 $a_i$ 是不是等于 $minn_i$ 即可。但是这样会有一个小问题，那就是 1 的最后一个可能大于 2 的第一个。所以我们加上这个特判就可以通过此题。但是我并不清楚这个做法的正确性，所以有大佬可以证明的话，就在此膜拜了。

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[200005];
int minn[200005];
vector<int> E,F;
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		E.clear(); F.clear();
		int n; scanf("%d%s",&n,a+1);
		minn[n+1]=114514;
		for(int i=n;i>=1;i--)
			minn[i]=min(minn[i+1],(int)a[i]);
		
		for(int i=1;i<=n;i++)
			if(a[i]==minn[i] && (!F.size() || a[i]-48<=F[0])) E.push_back(a[i]-48),a[i]=1;
			else F.push_back(a[i]-48),a[i]=2;
		bool flag=1;
		for(int i=0;i<F.size();i++)
			if(i!=0 && F[i]<F[i-1]) flag=0;
		if(!flag){puts("-"); continue;}
		for(int i=1;i<=n;i++) printf("%d",a[i]);
		putchar('\n');
	}
	return 0;
}
```

---

