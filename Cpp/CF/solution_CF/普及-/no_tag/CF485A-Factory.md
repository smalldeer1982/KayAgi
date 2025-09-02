# Factory

## 题目描述

有一个工厂，在一天的开始时，共有x条细节（？），在这一天结束时，会生产x mod m条细节。
 
 现在已知第一天所拥有的细节数a，以及m的值
 
请问，是否存在一个时刻，整个工厂会停止生产（x mod m = 0）？

## 样例 #1

### 输入

```
1 5
```

### 输出

```
No
```

## 样例 #2

### 输入

```
3 6
```

### 输出

```
Yes
```

# 题解

## 作者：CobaltChloride (赞：8)

```
//每次加上x%m,相当于加x,最后得到的一定是x*(2^n)的形式
//只要把m中2这个因子除去,若a%m==0就可以
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,m;
signed main(){
	cin>>a>>m;
	while(m%2==0) m/=2;
	if(a%m==0) cout<<"Yes";
	else cout<<"No";
    return 0;
}
```

---

## 作者：Rainbow_qwq (赞：6)

[原题](https://www.luogu.org/problemnew/show/CF485A)

思路：

深搜+标记。(搜索真是万能)

如果找到了，输出"Yes"退出程序。

如果遍历所有情况没找到，输出"No"。

**AC 代码 如下：**
```cpp
#include<cstdio>
#include<cstdlib>
#include<cctype>
using namespace std;
inline int read(){//快读模板
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}
const int maxn=1e5+10;//数据范围给了1<=a,m<=10^5
bool vis[maxn];		  //标记数组
int a,m;
void dfs(int x)
{
	if(x%m==0){//找到了
		puts("Yes");
		exit(0);	//用于直接退出程序
	}
	x=(x+x%m)%m;//根据题意改变x的值
	if(!vis[x]){
		vis[x]=1;//标记
		dfs(x);	 //下一步深搜
	}
}
int main()
{
	a=read();
	m=read();
	dfs(a);
	puts("No");//没找到，输出"No"
	return 0;
}
```

---

## 作者：Andysun06 (赞：3)

## CF485A 题解 
### 题目分析：
这个题的题面看得有点复杂（可能只有我这个蒟蒻觉得），但其实只要仔细思考一下，很容易就发现，这题的意思就是输入一个数 $n$，然后再枚举多次，如果在枚举的时候发现了 $a\%m==0$ 就直接输出 `Yes` 并且退出，否则 $a$ 一直加  $a\%m$ ，如果枚举到最后，还是没有退出程序，就输出 `No`
### 题目难度：
个人认为在入门难度左右
### 做法分析：
在题目分析我们已经说到了是输入两个数 $n,m$，然后再枚举多次（我选的是 $m+100$,但在我看别的题解释，$m+10$ 也可以），如果在枚举的时候发现了 $ a\%m==0 $ 就直接输出 `Yes` 并且退出，否则 $a$ 一直加 $a\%m$ 。如果枚举完了还没有退出，就证明不会有停止生产的情况，输出 `No` 就好了。
### 完整代码：
```
#include<cstdio>
#include<iostream>
long long a,m; //注意，a,m 一定要用long long不然会爆
int i;
int main() {
    scanf("%lld%lld",&a,&m); //输入，注意要用%lld
    if(a%m==0) { //如果刚开始时就会停产，直接输出"Yes"
        puts("Yes");
        return 0;
    }
    for(i=1; i<=m+100; i++) { //暴力枚举多次
        a+=a%m;
        if(a%m==0) {  //如果有a%m==0的情况，直接输出"Yes"
            puts("Yes");
            return 0; //记住要跳出
        }
    }
    puts("No"); //枚举完了还没有退出，就输出"No"
}
```
希望本题解对大家有帮助，也感谢管理员百忙之中为我审核题解，谢谢！

2020/3/14 修改爆掉的LaTeX。

---

## 作者：封禁用户 (赞：2)

这一题还行。首先，输入a与m。

接下来，就开始试。不知道是我运气好的缘故呢，反正试m+10次一定会出正确答案。

注意一下，a要用long long来存储。否则你第21个点就会错

以下是代码↓↓
```
#include <bits/stdc++.h>
using namespace std;
long long a,m;
int main()
{
    cin>>a>>m;
    for(int i=1;i<=m+10;i++)
    {
        if(a%m==0)
        {
            cout<<"Yes";
            return 0;
        }
        a=a+a%m;
    }
    cout<<"No";
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF485A)

## 题意分析
这道题重在思考，把结论得出来后只有红题的难度。

**我们发现**：

每一次的细节数 $x$ 必为 $a\times2^n$ 的形式。要判断某一时刻 $x\bmod m=0$，就要将 $m$ 里面的因子 $2$ 消去，再判断 $a\bmod m$ 是否等于 $0$。

## $\text{AC code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,m;
    cin>>a>>m;
    while(m%2==0) 
	{
		m/=2;
	}
    if(a%m==0) printf("Yes");
    else printf("No");
    return 0;
}
```


---

## 作者：Tx_Lcy (赞：1)

这是一道签到题，所以我来水一篇题解。
## 思路
首先我们可以发现不管这个生产的细节数为 $x \bmod\ m$ 还是 $x$，$x$ 加上它后 $\bmod \ m$ 的值是不变的。所以我们不妨设生产的细节数为 $x$。

那么我们在经过 $y$ 轮后的细节数为 $a \times 2^y$，对它进行分解质因数，我们发现 $x$ 仅仅是增添了 $2$ 这个质因子，其它的质因子是它本身存在的。所以我们不妨对 $a$ 和 $m$ 分解质因数，若一个质因子存在于 $m$ 却不存在于 $a$，答案一定是 $\verb!No!$，否则是 $\verb!Yes!$。

总时间复杂度 $O(\sqrt n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=1e5+10;
int p1[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int x,y;cin>>x>>y;
	int k=0,j=1;
	for (rint i=2;i<=x;++i){
	    if (x%i==0) p1[++k]=i;
	    while (x%i==0) x/=i;
	}
	for (rint i=2;i<=y;++i){
		if (y%i==0 && i!=2){
			if (i>p1[j]) ++j;
			if (i!=p1[j]){cout<<"No\n";return 0;}
		}
	    while (y%i==0) y/=i;
	}
	cout<<"Yes\n";
	return 0;
}
```


---

## 作者：lichenfan (赞：1)

### 思路
它每一天的细节是又前一天的得来的，可以直接循环模拟每一天的细节数，因为可能很大，所以要开 longlong，不然会炸。  
而循环调用的次数我来解释一下，因为要模 $m$，所以情况数只有 $m$ 种，即 $x$ 为 $0$ 到 $m-1$ 种可能的情况，所以只要模拟 $m$ 天即可，后面肯定有重复的。所以代码就很容易实现了。  
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long m,a;
int main(){
    cin>>a>>m;
    for(int i=1;i<=m;i++){ 
        if(a%m==0){
            cout<<"Yes";
            return 0;
        }
        a=a+a%m; 
        a%=m;
    }
    cout<<"No";
}
```


---

## 作者：_l_l_ (赞：0)

[题目页面](https://www.luogu.com.cn/problem/CF485A)

[更好的阅读体验](https://www.luogu.com.cn/blog/yinjun2024/solution-cf485A)

这道题使用数学

首先，由于每一天的细节是由前一天的细节 $\bmod \ m$ 得来的，因此由“抽屉原理”，细节数 $\bmod \ m$ 有循环节且循环节长度小于等于 $m$ 。

所以我们可以暴力枚举第一天后的 $m + 1$ 天，暴力判断。

如果你不想开 `long long`，那么必须随时取模。

代码：
```cpp
#include <cstdio>
int main() {
	int a, m;
	scanf("%d %d", &a, &m);
	for (int i = 0; i <= m; i++) {
		if (a % m == 0) {
			puts("Yes");
			return 0;
		}
		a += a % m;
		a %= m;
	}
	puts("No");
	return 0;
}
```

---

## 作者：G__G (赞：0)

这是我的第二篇题解，也是第一篇绿题题解。

# [醒目的传送门](https://www.luogu.com.cn/problem/CF485A)

## 题目描述

有一个工厂，在一天的开始时，共有 $x$ 条细节，在这一天结束时，会生产 $x \bmod m$  条细节。

现在已知第一天所拥有的细节数 $a$，以及 $m$ 的值。

请问，是否存在一个时刻，整个工厂会停止生产（$x \bmod m = 0$）?

## 求解过程

事先说明，这题需要极强的思维能力，不满足条件的人别往下看。

每一次的细节数 $x$ 必为 $a\times 2^n$ 的形式。要判断某一时刻 $x \bmod  m = 0$，就要将 $m$ 里面的因子 $2$ 消去，再判断 $a \bmod m$ 是否等于 $0$。

### 听完讲解，大家还想暴力吗？

那咱就

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,m;
    cin>>a>>m;
    while(m%2==0){
        m/=2;
    }
    if(a%m==0){
        cout<<"Yes";
    }
    else {
        cout<<"No";
    }
    return 0;
}
```

# [$AC$ 证明](https://www.luogu.com.cn/record/90458731)

题解来之不易，跪求管理员过审。

---

## 作者：Siteyava_145 (赞：0)

第一道绿题题解~~~

思维题。

每一次的细节数 $x$ 必为 $a\times2^n$ 的形式。要判断某一时刻 $x\bmod m=0$，就要将 $m$ 里面的因子 $2$ 消去，再判断 $a\bmod m$ 是否等于 $0$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,m;
    cin>>a>>m;
    //1 1[hack]
    while(m%2==0)m/=2;//×2的次数，把m中的2都消除掉
    if(a%m==0)cout<<"Yes";//若m|a,那么输出Yes.
    else cout<<"No";//否则输出No.
}
```


---

