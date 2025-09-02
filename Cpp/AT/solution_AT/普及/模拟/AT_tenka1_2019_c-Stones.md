# Stones

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_c

$ N $ 個の石が一列に並んでおり、すべての石は白か黒で塗られています。 石の状態は長さ $ N $ の文字列 $ S $ で表され、$ S $ の $ i $ 文字目が `.` のとき左から $ i $ 個目の石が白であり、`#` のとき左から $ i $ 個目の石が黒であることを表します。

高橋君は、$ 0 $ 個以上の石の色を黒または白に変更し、黒い石のすぐ右に白い石があるような箇所がないようにしたいです。 色を変更する必要のある石の個数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ S $ は `.`, `#` のみからなる長さ $ N $ の文字列である

### Sample Explanation 1

例えば、$ 1 $ 個目の石の色を白に変更すればよいです。

## 样例 #1

### 输入

```
3
#.#```

### 输出

```
1```

## 样例 #2

### 输入

```
5
#.##.```

### 输出

```
2```

## 样例 #3

### 输入

```
9
.........```

### 输出

```
0```

# 题解

## 作者：QWQ_SenLin (赞：2)

题目要求黑石头右边不能有白石头，然后询问最少染色数量。

大约就是让我们染成以下形式。

```
...（a个白色） + ###（b个黑色）   a + b = N
```

$N$ 的数据范围不大，直接枚举黑白之间的点就行了，至于每种可行的排列下的答案，就是左边需要染成白色的数量+右边需要染成黑色的数量。

至于实现，用前缀和预处理好在 $i$ 之前黑色的数量，然后枚举并更新答案就好了。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n , ans = 0x7fffff;
char c[200005];
int sum[200005];

int main(void){
    scanf("%d%s" , &n , c + 1);
    for(int i = 1;i <= n;i++)
        sum[i] = sum[i - 1] + (c[i] == '#');
    //前缀和求黑色的数量
    for(int i = 1;i <= n + 1;i++) //要遍历到n+1，因为可能需要全部涂白
        ans = min(ans , sum[i - 1] + (n - i + 1 - (sum[n] - sum[i - 1])));
        //用i前面黑色的数量+i后面（包括i）白色的数量
    printf("%d\n" , ans);
}
```

---

## 作者：xxr___ (赞：1)

### 思路：
本题有几个特判情况，如果全是白色，就输出一，否则我们考虑此题做法，首先，数据范围较大，只能承受住线性复杂度，所以我们想那些算法是线性呢？枚举？递推？想到了前缀和和差分，于是我们想到可以用前缀和统计黑色的数量，枚举判断一个黑色的前后是否有白色色就行了。
### 代码：
```cpp
#include<bits/stdc++.h>
int n,INF=0x3f3f,sum[1000005];
std::string s;
signed main(){
	std::cin>>n>>s;
	int v=0;
	for(char c:s)v+=(c=='.');
	if(v==n)return puts("0")&0;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i-1]=='#');
	for(int i=1;i<=n+1;i++)INF=std::min(INF,sum[i-1]+(n-i+1-(sum[n]-sum[i-1])));
	std::cout<<INF<<"\n";
}
```

---

## 作者：Fkxxx (赞：1)

### 题意

给出一段字符串，你要通过最少的修改次数使得它所有的 `#` 右侧都是 `.`。

求最小步数。

### 思路

我们发现，符合这个要求的答案只有可能是形如一下示例的字符串。

```
......
.....#
....##
...###
..####
.#####
######
```

形式化地，对于一个符合要求的结果，总能找到一个 $pos$，$1 \thicksim pos - 1$ 均为 `.`，$pos \thicksim n$ 均为 `#`。

所以我们只需枚举每一种可行的方案，取步数的最小值，最后输出即可！

因为总共只有 $n+1$ 种方案，所以，我们只要对原字符串取前缀和，时间复杂度就是 $O( n )$。

### ACCODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , a[200005] , b[200005] , c[200005] , ans = 1e9 ;
signed main(){
    cin >> n ;
    for( int i = 1 ; i <= n ; i ++ ){
        char u ;
        cin >> u ;
        if( u == '.' ){
            a[i] = 1 ;
        }
    }
    for( int i = 1 ; i <= n ; i ++ ){
        b[i] = b[i - 1] + !a[i] ;
    }
    for( int i = n ; i >= 1 ; i -- ){
        c[i] = c[i + 1] + a[i] ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        ans = min( b[i] + c[i] - 1 , ans ) ;
    }
    cout << ans ;
    return 0 ;
}
```

---

## 作者：OLE_OIer (赞：1)

## AT4920 Stones 

这道题是一道不错的初级字符串模拟题。

题目大意：$n$ 块石头排一排，要使得一块黑石头右边没有紧贴的白石头，至少改变多少块石头的颜色。

首先，我们要知道，若有一块石头为黑，则它右边的一个必须得是黑（因为不能是白）。那么它右边的右边也得是黑……以此类推，我们可以得到只要有一个石头颜色为黑，那么它右边所有的石头均为黑。

所以因为数据范围不大，所以我们直接暴力枚举就好了。只需要枚举第一个黑石头的位置即可。

注意：重复计算需要修改几块石头的颜色会超时，于是我们可以用前缀和优化的方法来做。

代码附上：
```cpp
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
int cntb[200010],cntw[200010];
//cntb[i] 表示第 i 个石头机器之前有几块黑石头，cntw[i] 表示第 i 个石头机器之前有几块白石头
int minn=INT_MAX;//最小值
signed main(){
	int len;string s;cin>>len>>s;//len 表示共有几块石头。
	s='$'+s;//避免出现 0 的bug
	for(int i=1;i<=len;++i) cntb[i]=cntb[i-1]+(s[i]=='#'),cntw[i]=cntw[i-1]+(s[i]=='.');
	for(int i=0;i<=len;++i) minn=min(minn,cntb[i]+cntw[len]-cntw[i]);
	cout<<minn<<"\n";
	return 0;
}
```

如果有任何问题可以在评论区或私信来询问笔者，笔者会尽快回答的。

---

## 作者：fnoiylin (赞：1)

题意分析 : 在 $ n $ 个石块中 最少改变多少个石头的颜色    , 使黑色石头左边没有白色石头

符合题意的答案只有几个 : 

 $ e g : n = 3 $ , 成功的方案有 

 黑 黑 黑

 白 黑 黑

 白 白 黑

 白 白 白

能够发现一个规律 : 只要出现一个黑石头 : 后面的全部是黑石头 . 

所以我们只需要枚举断点 ( 从哪里开始变成黑石头 ) 记下改变的个数并找到最小值

 AC代码 : 

``` cpp

#include<bits/stdc++.h>
using namespace std;
const int N=220000; 
int n,cnt0[N],cnt1[N],ans;
char a[N];
int main(){
    scanf("%d%s",&n,a+1);
    for(int i=1; i<=n; i++)cnt0[i]+=a[i]=='#',cnt1[i]+=a[i]=='.';//是为1，不是为0，直接加 
	//即判定第i个石头是黑是白并记录 
    for(int i=1; i<=n; i++)cnt0[i]+=cnt0[i-1],cnt1[i]+=cnt1[i-1];
    //cnt0[i]是到第i个石头有多少黑石头，cnt1则是白石头 
    ans=n;//最多修改全部，即n 
    for(int i=0; i<=n; i++)ans=min(ans,cnt0[i]+cnt1[n]-cnt1[i]);//注意i从0开始，计算全黑情况 
	//备选答案为断点前面的黑石头数+断点和后面的白石头数找到最小值 
    printf("%d\n",ans);
    return 0;
}

```


---

## 作者：zgy_123 (赞：0)

本题思维难度不高，代码更是只有十几行，建议降橙。

首先分析题目，一个黑石子右边不能是白石子，所以黑石子旁边只能是黑石子。而第二个黑石子旁边还是只能为黑石子，以此类推，我们发现整个序列的右半部分必须全都是黑石子，而左半部分必须全是白石子。

这样整个问题就解开了，我们只需要枚举每个位置，将它左边（包含）全部修改为白石子，右边（不包含）全部修改为黑石子，为了能 $O(1)$ 计算，还需要加上一个前缀和数组 `p`。

我们假设数组 `a` 中黑石子为 `1`，白石子为 `0`，第 $i$ 个位置的贡献化简为：

$\text{ }\sum_{j=0}^{i} a_i + ( n - i - \sum_{j=i+1}^{n} a_i )$

$=p_i+(n-i-(p_n-p_i))$

$=p_i+n-i-p_n+p_i$

$=n-i-p_n+2p_i$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],p[200005];
int main(){
	int n,ans;
	cin>>n;
	for(int i=1;i<=n;i++){
		char x;
		cin>>x;
		if(x=='#') a[i]=1;
		p[i]=p[i-1]+a[i];
	}
	ans=p[n];
	for(int i=0;i<=n;i++) ans=min(ans,n-i-p[n]+p[i]*2);
	cout<<ans;
	return 0;
}

```

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_tenka1_2019_c)

# 题意

要使黑石头右边没有白石头，至少要改变多少石头的颜色。

# 思路
先枚举黑石头的个数，然后求 a 前面一段黑石头个数和后面一段白石头个数之和，可用前缀和，最后枚举最小的答案。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,mi=1e9,s[200001];
string a;
int main(){
    cin>>n>>a;
    a=" "+a;
    for(i=1;i<=n;i++)
        if(a[i]=='#') s[i]=s[i-1]+1;
        else s[i]=s[i-1];//前缀和求黑石头数量
    for(i=0;i<=n;i++)//注意i从0到n
        mi=min(mi,s[n-i]+i-s[n]+s[n-i]);//i前面黑石头+i后面白石头
    cout<<mi;
    return 0;
}
```


---

## 作者：Silence_World (赞：0)

# 题意

给你一个 $n$ 为长度的字符串，其中字符只包括黑白两种字符，要求黑字符后面全部是黑字符，可以任意更改每个点的颜色，问实现这个操作的最小次数是多少？

# 思路

比较基础的一道题，既然可以改变字符的任意颜色，其实也就无非两种情况：

第一种：找到一个点，把他改为白色，前面的也全改为白色。

第二种：找到一个点，把他改为黑色，后面也全部改为黑色。

很显然，我们可以用前缀后缀和来记录黑色字符与白色字符出现的个数，这样题就变成了找一个点了，只需要跑一遍所有的点，找到前面黑色字符的个数与后面白色字符的个数相加之和的最小值就可以了。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
int b[1000005];
signed main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	bool fl=0;
	int sum=0;
	for(int i=0;i<n;i++){
		if(s[i]=='#'){
			a[i]++;
		}
		a[i]+=a[i-1];
	}
	for(int j=n-1;j>=0;j--){
		if(s[j]=='.'){
			b[j]++; 
		}
		b[j]+=b[j+1];
	}
	int ans=10000005;
	for(int i=0;i<n;i++){
		ans=min(ans,a[i-1]+b[i+1]);
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：KυρωVixen (赞：0)

## 题意：
可转化为：求一个点，使得这个点以及其左边的黑点数加上其右边的白点数最小。

$N\le2\times10^5$。

## 解法：
比较一眼。可以预处理出前缀的黑点数和后缀的白点数，然后枚举中间点即可。

时间复杂度 $O(N)$。

## 代码：
```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)
#define Puts(x) cout<<x<<'\n'
using namespace std;
const int N=2e5+5;
int n,ans=INF,a[N],qz1[N],qz2[N];
signed main(){
	cin>>n;
	rep(i,1,n){
		char x; cin>>x; a[i]=(x=='.')?1:2; 
	}
	rep(i,1,n) qz1[i]=qz1[i-1]+(a[i]==2);
	repr(i,n,1) qz2[i]=qz2[i+1]+(a[i]==1);
	rep(i,1,n) ans=min(ans,qz1[i]+qz2[i]-1);
	Puts(ans);
}
```

---

## 作者：Night_sea_64 (赞：0)

其实，题目中所说的目标状态就是先一片白，然后一片黑（也可以全白或全黑）。

枚举黑色个数 $i$ 从 $0$ 到 $n$。然后求出 $S$ 前面一段（$1\sim n-i$）黑色个数和后面一段（$n-i+1\sim n$）白色个数之和即为答案，可用前缀和求解。对于枚举的所有 $i$ 取最小的答案即可。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int sum[200010],n,minn=1e9;
string s;
int main()
{
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+(s[i]=='#');
    for(int i=0;i<=n;i++)
        minn=min(minn,sum[n-i]+i-sum[n]+sum[n-i]);
    cout<<minn<<endl;
    return 0;
}
```

---

## 作者：Federico2903 (赞：0)

非常基础的一道字符串题。  
读完题目可以理解到，一块黑石头的右边必为黑石头，而这块黑石头的右边也必为黑石头，也就是说，最左边黑石头的右边一定全都是黑石头。  
这样我们就把序列分成了两部分，一部分全都是白石头，在左边，一部分全都是黑石头，在右边。  
我们只要枚举这个分开的点即可，左边的全部改成白石头，右边的全部改成黑石头。用前缀和记录前后的黑白石头数即可AC。  

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,qz[200005],hz[200005];
string s;
int main(){
	cin >> n >> s;
	if(s[0]=='.')qz[0]=0;
	else qz[0]=1;
	for(int i=1;i<n;i++){
		if(s[i]=='#')qz[i]=qz[i-1]+1,hz[i]=hz[i-1];
		else qz[i]=qz[i-1],hz[i]=hz[i-1]+1;//为了方便把后缀用前缀的方法计算
										   //其实是为了省几行代码（
	}
	int ans=1e9;//初始化极大值
	for(int i=0;i<=n;i++){
		ans=min(ans,qz[i]+hz[n-1]-hz[i]);
	}
	cout << ans;
}
```

---

