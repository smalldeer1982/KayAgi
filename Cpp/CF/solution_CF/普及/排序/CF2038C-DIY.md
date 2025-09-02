# DIY

## 题目描述

给定一个长度为 $n$ 的整数数列 $a$，下标从 $1$ 到 $n$。你需要从 $a$ 中选择 $8$ 个下标互不相同的数 $x1,y1,x2,y2,x3,y3,x4,y4$，并使 $(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$ 成为一个长方形的四个点的坐标。请构造一种方案使得此长方形面积最大，或报告无解。

## 样例 #1

### 输入

```
3
16
-5 1 1 2 2 3 3 4 4 5 5 6 6 7 7 10
8
0 0 -1 2 2 1 1 3
8
0 0 0 0 0 5 0 5```

### 输出

```
YES
1 2 1 7 6 2 6 7
NO
YES
0 0 0 5 0 0 0 5```

# 题解

## 作者：WangYongkai__AFO (赞：6)

## 本人第一篇题解
  **Solution：**

首先我们简化一下题意，其实题目求得就是在给定的 $n$ 个数中能否选出 $8$ 个数作为矩形四个顶点的坐标，若能则尽量是矩形面积最大，输出`Yes`以及四点坐标，否则输出`No`。

赛时思路：通过手动模拟一下我们得知，给定的 $n$ 个数中能够作为矩形四点坐标的数 $x$ 要满足 $x$ 的数目 $\ge2$ ，所以我们可以开一个 `map` 来计算每个数出现的次数，同时开一个 `vector` 将能够作为矩形顶点坐标的数 `push_back` 进去，如果 `vector.size()<4` ，则说明给出的数无法选出满足条件的四个数，直接输出 `No` 。如果 `vector.size()>=4` 再对 `vector` 排序，选最小、次小、最大、次大的四个数，分别输出坐标即可。

本题坑点：

1. $-1e9 \leq a[i] \leq 1e9$ ，因此我们计数是只能用 `map` ，而不能用数组，否则会 `RE` （像我一样喜提一发罚时）。

2.在计数的时候，若某个数已经出现了 $2$ 次，在 `push_back` 的同时要将它对应的计数个数清零，因为会出现选择 $8$ 个相同的数作为顶点坐标的情况。

3.输出时要仔细考虑四个数的坐标关系再输出。

**代码如下：**


```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<stack>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<set>
#include<bitset>
#include<iomanip>
#include<cstdlib>
#define int long long
using namespace std;
int T;
int n;
const int N=2e5+5;
int a[N];
vector<int>e;
signed main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {
        e.clear();
        map<int,int>vis;
        cin>>n;
        for(int i=1;i<=n;i++) 
        {
            cin>>a[i],vis[a[i]]++;
            if(vis[a[i]]==2) 
            {
                e.push_back(a[i]);
                vis[a[i]]=0;
            }
        }
        if(e.size()<4)
        {
            cout<<"No"<<'\n';
            continue;
        }
        sort(e.begin(),e.end());
        int len=e.size();
        cout<<"Yes"<<'\n';
        cout<<e[len-1]<<' '<<e[len-2]<<' '<<e[len-1]<<' '<<e[0]<<' '; 
        cout<<e[1]<<' '<<e[len-2]<<' '<<e[1]<<' '<<e[0]<<'\n';
    }
     return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：1)

## 题意

给定长度为 $n$ 的序列 $a$，选 $8$ 个数组成 $4$ 个坐标，使形成的矩形面积最大。

## 思路

要构成矩形至少要有 $2$ 个坐标 $x$ 或 $y$ 相同，这就是判无解的方法。而要选面积最大，四个角（顺序为左下 $(x_1,y_1)$、左上 $(x_2,y_2)$、右下 $(x_3,y_3)$、右上 $(x_4,y_4)$）分别是 $x_1,y_1,x_2,y_3$ 最小，$y_2,x_3,x_4,y_4$ 最大。对 $a$ 排序后贪心选，要注意数字个数，按顺序输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c,d) for(int a=b;a<=c;a+=d)
#define R(a,b,c,d) for(int a=b;a>=c;a-=d)

using namespace std;
const int N=2e5+5,M=998244353;

void solve();
int T,n,a[N],b[10];
map<int,int> m;

signed main(){
  scanf("%d",&T);
  while(T--) solve();
  return 0;
}

void solve(){
  scanf("%d",&n);
  m.clear();
  L(i,1,n,1){
    scanf("%d",a+i);
    m[a[i]]++;
  }
  sort(a+1,a+n+1);
  int sum=0;
  a[0]=1e9+5;
  L(i,1,n,1){
    if(m[a[i]]>1&&a[i]!=a[i-1]){
      if(m[a[i]]<=3) sum+=2;
      else if(m[a[i]]<=5) sum+=4;
      else if(m[a[i]]<=7) sum+=6;
      else sum+=8;
    }
  }
  if(sum<8){
    printf("NO\n");
    return;
  }
  int j=1;
  while(m[a[j]]<2) j++;
  if(m[a[j]]<4){
    b[1]=a[j],b[3]=a[j];
    while(a[j]==a[j+1]) j++;
    j++;
    while(m[a[j]]<2) j++;
    b[2]=a[j],b[6]=a[j];
  }
  else{
    b[1]=a[j],b[2]=a[j],b[3]=a[j],b[6]=a[j];
  }
  j=n;
  while(m[a[j]]<2) j--;
  if(m[a[j]]<4){
    b[4]=a[j],b[8]=a[j];
    while(a[j]==a[j-1]) j--;
    j--;
    while(m[a[j]]<2) j--;
    b[5]=a[j],b[7]=a[j];
  }
  else{
    b[4]=a[j],b[5]=a[j],b[7]=a[j],b[8]=a[j];
  }
  printf("YES\n");
  L(i,1,8,1) printf("%d ",b[i]);
  printf("\n");
}
```

---

## 作者：GCSG01 (赞：1)

### 题意
要取 $8$ 个点分别作为坐标组成一个矩形，并使矩形面积最大，输出一种方案。
### 思路
思考怎么取 $4$ 个点使得矩形最大，则四个横坐标中，要有两个很小，另外两个很大，纵坐标同理，我们可以对数组进行排序，然后再取最值，要注意取的时候不能重复选取一个点，其他的看看代码吧，主要是细节问题。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int a[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
    #endif
    int t;
    cin>>t;
    while(t--)
    {
        int n;cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);
        int minn1=1e9+1,minn2=1e9+1,maxx1=-1e9-1,maxx2=-1e9-1,f=0;
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]!=a[i-1])cnt=0;
            cnt++;
            if(cnt>=2)cnt-=2,f++;
        }
        if(f<4)
        {
            cout<<"NO\n";
            continue;
        }
        cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]!=a[i-1])cnt=0;
            cnt++;
            if(cnt>=2)minn1=min(minn1,a[i]),maxx1=max(maxx1,a[i]);//先取一遍最值，不然不好判重复
        }
        cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]!=a[i-1])cnt=0;
            cnt++;
            if(cnt>=4)minn2=min(minn2,a[i]),maxx2=max(maxx2,a[i]);
            if(a[i]!=minn1&&cnt>=2)minn2=min(minn2,a[i]);//
            if(a[i]!=maxx1&&cnt>=2)maxx2=max(maxx2,a[i]);//防止取重复的数字
        }
        cout<<"YES\n";
        int t=minn1,t2=maxx1;
        minn1=min(minn1,minn2),maxx1=min(maxx1,maxx2);
        minn2=max(minn2,t),maxx2=max(maxx2,t2);//调换顺序，因为两个相近的数乘积更大
        cout<<minn1<<" "<<minn2<<" "<<minn1<<" "<<maxx2<<" ";
        cout<<maxx1<<" "<<minn2<<" "<<maxx1<<" "<<maxx2<<"\n";
    }
    return 0;
}
```

---

## 作者：ivyjiao (赞：1)

水题，十分钟切了。

很明显我们需要找到 $4$ 组数对 $(x,x)$。其中两组 $x$ 可以相同。

然后我们想到：

1. 若数对数量 $<4$，无解。
2. 观察样例 $1$ 我们得到了一个很好的性质：我们需要找到 $x$ 第 $1,2$ 小的数对，和第 $1,2$ 大的数对，按照样例 $1$ 所给的顺序输出即可，至于找数对，直接排序就行。

设第 $1,2$ 小的数对为 $x_1,x_2$，第 $1,2$ 大的数对为 $x_3,x_4$，由于我们要保证左下角的点 $(x,y)$ 尽可能小，右上角的点 $(x,y)$ 尽可能大，那么我们要找的点显然为 $(x_1,x_2),(x_1,x_4),(x_3,x_2),(x_3,x_4)$，按照任意顺序输出（点的 $(x,y)$ 不可改变）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
unordered_map<int,int>mp;
int t,n,a[N];
vector<int>b;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            mp[a[i]]++;
        }
        for(int i=1;i<=n;i++){
            if(mp[a[i]]>1){
                mp[a[i]]-=2;
                b.push_back(a[i]);
            }
        }
        sort(b.begin(),b.end());
        if(b.size()<4) cout<<"NO"<<endl;
        else{
            cout<<"YES"<<endl;
            cout<<b[0]<<" "<<b[1]<<" "<<b[0]<<" "<<b[b.size()-1]<<" "<<b[b.size()-2]<<" "<<b[1]<<" "<<b[b.size()-2]<<" "<<b[b.size()-1]<<endl;
        }
        b.clear();
        mp.clear();
    }
}
```

---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF2038C) & [CF 题目链接](https://www.luogu.com.cn/record/list?pid=CF2038C)

# 题意简述

给你一些正整数，你需要从中选出 $8$ 个两两组成共 $4$ 个点的坐标，使得这 $4$ 个点围成的矩形四边都与坐标轴平行且该矩形面积最大，按任意顺序依次输出 $4$ 个点的坐标，或报告无解。

# 思路分析

仔细观察样例发现，要想使得组成的矩形与坐标轴平行，选出的 $8$ 个数中必须两两相同，也就是只有 $4$ 个数且每个数出现两次。如下图，设左下角与右上角的顶点坐标分别为 $(a,b)$ 和 $(c,d)$，那么就可以用 $a,b,c,d$ 表示出左上角和右上角的点的坐标。

![](https://cdn.luogu.com.cn/upload/image_hosting/sem9row3.png)

矩形面积为 $(d-b)\times(c-a)$。

显然为了使矩形面积最大 $a,b$ 是原数组中出现两次及以上的数的最小值和次小值，同理 $c,d$ 是原数组中出现两次及以上的数的最大值和次大值。

那么我们可以把原数组中出现两次及以上的数放入一个新数组中，如果出现了 $4$ 次就放 $2$ 个后面同理，然后对新数组排序。如果新数组中不够 $4$ 个元素就是无解，否则找出开头的两个数和结尾的两个数，比较 $a,b,c,d$ 怎么搭配面积最大然后输出。

赛时脑抽使用了 multiset。

# 代码


```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=200003,inf=0x3f3f3f3f;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int T,n;

map<int,int>mp;

multiset<int>st;

void out(int a,int b,int c,int d){
	printf("%lld %lld %lld %lld %lld %lld %lld %lld\n",a,d,c,d,a,b,c,b);
	return;
}

signed main(){
	T=read();
	while(T--){
		mp.clear();
		st.clear();
		n=read();
		while(n--){
			int x=read();
			mp[x]++;
		}
		for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
			int x=(*it).second,y=(*it).first;
			while(x>=2){
				x-=2;
				st.insert(y);
			}
		}
		if(st.size()<4){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		int a=*st.begin();
		st.erase(st.begin());
		int b=*st.begin();
		int c=*st.rbegin();
		st.erase(st.lower_bound(*st.rbegin()));
		int d=*st.rbegin();
		if((d-a)*(c-b)<(d-b)*(c-a)){
			out(a,b,c,d);
		}else{
			out(a,b,d,c);
		}
	}
	return 0;
}
```

---

