# Homecoming

## 题目描述

Petya 开完了派对，想回家。

我们可以把整个城市抽象成一条直线，开派对的地方在直线的一端，Petya 的家在直线的另一端。

直线上有一些公交车站（用 'A' 表示）和一些电车站（用 'B' 表示）。

Petya 可以支付 $a$ 元从一个车站坐到另一个车站，但乘车的路程中路过的必须是公交车站（包括起点不包括终点）。

Petya 可以支付 $b$ 元从一个车站坐到另一个车站，但乘车的路程中路过的必须是电车站（包括起点不包括终点）。

但是 Petya 的只有 $p$ 元，所以你要帮她算出她至少要步行几站才能到家？


第二行一个字符串，由'A'和'B'组成，表示这条路上的车站。

## 说明/提示

$1 \le t \le 10^4$ ，$1 \le a, b, p \le 10^5 $ ，$ 2 \le |s| \le 10^5 $

## 样例 #1

### 输入

```
5
2 2 1
BB
1 1 1
AB
3 2 8
AABBBBAABB
5 3 4
BBBBB
2 1 1
ABABAB```

### 输出

```
2
1
3
1
6```

# 题解

## 作者：pyqpyq (赞：4)

# 题目大意
Petya 手上有 p 块钱，他开完了派对，想回家。

回家的路上有 n 个路口，每个路口都有一个公交车站（用‘A’表示）或一个电车站（用‘B’表示）。Petya 的家就在

他每次都可以花 a 块钱从一个路口坐到另一个路口，并且这两个路口之间的车站要都是公交车站（包括起点但不包括终点）。

同样地，他每次都可以花 b 块钱从一个路口坐到另一个路口，并且这两个路口之间的车站要都是电车站（包括起点但不包括终点）。

但是 Petya 的钱可能不够，所以他要走一段路。但是他一但坐了车就不想走路了。问他最少要走多少站。
# 题目分析
首先通过样例可以得出一个显然的结论：最优的做法是直接从一个上一个路口是电车站的公交车站坐到下一个电车站或者从一个上一个路口是公交车站电站坐到下一个公交车站。

这样我们就可以 $O(n)$ 判断一个方案是否合法了。从当前枚举的答案开始，每经过一对不同的车站就把当前记录的钱数増加，如果超过了 p 则答案不正确，如果到家了则答案正确。

~~可以感性理解其正确性。~~

所以我们就可以二分答案了，总复杂度 $O(n \log n)$，**也许**可以通过本题数据（我没试过）。

~~此题完结。~~
# 算法优化
有没有复杂度更优的算法呢？

注意到坐车的区间左端点是没有确定的，而右区间端点是确定的，所以我们可以倒过来考虑。

判断过程差不多，从右边往左边扫，每次遇到上一个路口与这一个路口类型不一样就说明要多花钱了。如果到此站钱就花完了那么本站就是答案。如果到头钱还没花完，那么答案就是 1。
# 完整代码
~~终于有我放完整代码的题解了。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,p,n,l;
char s[100011];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%s",&a,&b,&p,s);
		n=strlen(s);
		s[n-1]='C';
		l=1;
		for(int i=n-1;i>=1&&l;--i)
		{
			if(s[i-1]!=s[i]&&s[i-1]=='A'&&(p-=a)<0)
			{
				printf("%d\n",i+1);
				l=0;
				break;
			}
			else if(s[i-1]!=s[i]&&s[i-1]=='B'&&(p-=b)<0)
			{
				printf("%d\n",i+1);
				l=0;
				break;
			}
		}
		if(l)
			printf("1\n");
	}
	return 0;
}
```
其中 l 记录是否在中途就出解了。

要注意到家就一定要下车，所以要把 $s_{i-1}$ 赋为‘C’。

好像有的算法会爆 int？所以你要是不确定你的代码是否会爆 int 的话就开 longlong 吧。

完结撒花\\(^o^)/

---

## 作者：Lates (赞：3)

## 做法：二分答案

很显然，我们二分的是走路到达的点，check函数判断从该点能否到达目标点即可。

check函数$O(n)$复杂度，二分答案$(\log n)$

所以总时间复杂度就是$O(n \log n)$。

$Code$ ： 

```
#include <iostream>
#include <cstdio>
using namespace std;
inline int read(){
	register int x=0,v=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')v=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return x*v;
}
const int MAX=100005; 
int l,r,f[MAX],t,a,b,p,n,mid;
string s;
int tot;
inline bool check(int now){//check判断二分出来的点能否到达目标点
	if(now==n)return true;
	tot=(f[now]==1?a:b);//tot记录需要用的花费
	for(register int i=now+1;i<n;++i){
		if(f[i]!=f[i-1]){
			tot+=(f[i]==1?a:b);
			if(tot>p)return false;
		}
	}
	return tot<=p;//若tot<=p，返回true，否则返回1,表示花费<=有的钱数
}
int main(){
	t=read();
	while(t--){
		a=read(),b=read(),p=read();
		cin>>s;
		n=s.length();
		for(register int i=0;i<n;++i)f[i+1]=(s[i]=='A'?1:0);//1:bus 0:tram
		l=1,r=n;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid))r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",l);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

此题让我们求小 $P$ 要走多少站。我们经过读题后不难发现他走的站数是不确定的，而终点是确定的，那我们整理一下就是一个区间的左端点不确定，右端点确定。那我们就可以从后往前搜，搜到一个站钱花完了，那么就是到这个站。如果搜到头还没花完钱，那他就只用走 $1$ 站。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T, a, b, fw;
string s;
int main()
{
	cin >> T;
	while(T --)
	{
		cin >> a >> b >> fw >> s;
		s[s.size() - 1] = '艹';
		int p = 1;
		for(int i = s.size() - 1; i >= 1; -- i)
		{
	//		fw = fw - (s[i - 1] == 'A' ? a : b);
			if(s[i - 1] != s[i] && s[i - 1] == 'A' && (fw = fw - a) < 0 || s[i - 1] != s[i] && s[i - 1] == 'B' && (fw = fw - b) < 0)
			{
				cout << i + 1 << endl;
				p = 0;
				break;
			}
		}
		if(p) cout << "1\n";
	}
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
扫描，如果遇见不同的字符则扣除相应的钱，否则继续扫描。

由于到了家一定要下车，而在哪上车可以随便，所以从后往前扫描，钱不够了则输出。

### 手玩样例：
以 `AABBBBAABB` 为例。

倒推：

`B` 扣去 $2$ 元。

`AB` 扣去 $3$ 元。

`BBBBA` 扣去 $3$ 元。

此时钱花完了，所以需要走 `AAB` 的长度（即 $3$）站。

明白了算法，代码就很容易写了。具体细节看代码注释。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,a,b,c,p,len;
bool flag;
string s;
int main()
{
    ios::sync_with_stdio(0);
    cin >> t;
    while(t--)
    {
        cin >> a >> b >> p;
        cin >> s;
        flag = true;//记录是否需要跳出
        len = s.length();
        s[len-1] = 'O';//改一下终点的字符，使扫描到终点时会强制扣款
        while(len--)
        {
            if(s[len] != s[len-1])//判断是否到站
            {
                switch(s[len-1])//如果是则扣相应的款（不推荐用 switch，我因为太久没用才用的）
                {
                    case 'A':
                        p -= a;
                        break;//一定不要忘记 break！本蒟蒻因为忘写 break 调试时总出问题
                    case 'B':
                        p -= b;
                        break;//这个 break 无所谓
                }
                if(p < 0)//判断钱是否不够花
                {
                    cout << len+1 << '\n';
                    flag = false;//记录钱不够花了
                    break;
                }
            }
        }
        if(!flag)
            continue;
        cout << "1\n";//如果钱够花，则输出1
    }
    return 0;
}
```

---

