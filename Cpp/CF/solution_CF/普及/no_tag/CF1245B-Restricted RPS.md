# Restricted RPS

## 题目描述

$Alice$和$Bob$要玩石头剪刀布的游戏$n$次（$n$是正整数），$Alice$已经知道$Bob$每局要出什么。但是她只能出$a$次石头，$b$次剪刀和$c$次布（$a,b,c$为非负整数，且保证$a+b+c=n$）

$Alice$赢的条件是她**击败了**$Bob$至少 $\left\lceil\dfrac{n}{2}\right\rceil$次（向上取整），否则她输了

石头剪刀布的规则

- 石头赢剪刀
- 布赢石头
- 剪刀赢布

你的任务是，对于已给出的$Bob$的出手序列，和$a,b,c$，判断$Alice$是否能赢。如果能，找到$Alice$的出手序列

如果存在多组解，输出任意一个即可

## 样例 #1

### 输入

```
2
3
1 1 1
RPS
3
3 0 0
RPS
```

### 输出

```
YES
PSR
NO
```

# 题解

## 作者：andyli (赞：2)

对于Bob的每次出的东西，Alice采用贪心的策略，若能应对，则本轮应打败Bob。统计完可应对的次数$cnt$后，若$cnt \geq \left\lceil\dfrac{n}{2}\right\rceil=\left\lfloor\dfrac{n+1}{2}\right\rfloor$，则剩下不能应对的可以随便出，否则Alice就输了。  
主要代码如下：  
```cpp
int main()
{
    int T;
    io.read(T);
    while (T--) {
        int n, a, b, c;
        io.read(n, a, b, c);
        char str[105], ans[105];
        io.read(str);
        memset(ans, 0, sizeof(ans));
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (str[i] == 'R')
                if (b)
                    cnt++, b--, ans[i] = 'P';
            if (str[i] == 'P')
                if (c)
                    cnt++, c--, ans[i] = 'S';
            if (str[i] == 'S')
                if (a)
                    cnt++, a--, ans[i] = 'R';
        }
        ans[n] = 0;
        if (cnt >= (n + 1) / 2) {
            printf("YES\n");
            for (int i = 0; i < n; i++)
                if (!ans[i]) {
                    if (a)
                        a--, ans[i] = 'R';
                    else if (b)
                        b--, ans[i] = 'P';
                    else if (c)
                        c--, ans[i] = 'S';
                }
            printf("%s\n", ans);
        } else
            printf("NO\n");
    }
    return 0;
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1245/B)
我们需要为 Alice 构造一个出手序列，使得她能够击败 Bob 至少 $\lceil \frac{n}{2} \rceil$ 次。Alice 的出手次数必须满足给定的限制（$a$ 次石头，$b$ 次剪刀，$c$ 次布）。

## 思路
根据直觉，可以猜测策略为：

**对于 Bob 的每一次出手，Alice 需要选择一个能够击败 Bob 的出手（如果可能）。**

因为先击败和后击败意义一样，所以策略正确。

先尽可能多地击败 Bob，后面随便出招即可。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n;
	int a, b, c;
	string s;
	cin >> n >> a >> b >> c >> s;
	// 统计 Alice 的出手次数
	int win = 0;
	string t(n, ' ');
	// 首先尽可能多地击败 Bob
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'R' && b > 0) {
			t[i] = 'P';
			b--;
			win++;
		} else if (s[i] == 'P' && c > 0) {
			t[i] = 'S';
			c--;
			win++;
		} else if (s[i] == 'S' && a > 0) {
			t[i] = 'R';
			a--;
			win++;
		}
	}
	// 如果击败次数不足，输出 NO
	if (win < (n + 1) / 2) {
		cout << "NO\n";
		return;
	}
	// 填充剩余的出手
	for (int i = 0; i < n; ++i) {
		if (t[i] == ' ') {
			if (a > 0) {
				t[i] = 'R';
				a--;
			} else if (b > 0) {
				t[i] = 'P';
				b--;
			} else if (c > 0) {
				t[i] = 'S';
				c--;
			}
		}
	}
	cout << "YES\n";
	cout << t << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn) $，可以通过本题。

---

## 作者：RioFutaba (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1245B)
## 思路

贪心。能打赢的就打赢，打不赢的拿还没有出完的次数补。

然而实际实现有些麻烦，具体看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
int n,a,b,c;
string st;
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		cin >> a >> b >> c;
		cin >> st;
		string ans;
		ans.resize(n);
		int cnt=0;
		for(int i=0;i<n;i++){
			//判断有没有能力赢
			if(st[i]=='S'){
				if(a>0) ans[i]='R',a--,cnt++;
			}else if(st[i]=='R'){
				if(b>0) ans[i]='P',b--,cnt++;
			}else{
				if(c>0) ans[i]='S',c--,cnt++;
			}
		}
		if(cnt>=(n+1)/2){//判断输赢
			cout << "YES\n";
		}else{
			cout << "NO\n";
			continue;
		}
		for(int i=0;i<n;i++){
			if(ans[i]!='R' && ans[i]!='P' && ans[i]!='S'){//如果这一次打不赢就拿出剩下的补
				if(a>0) ans[i]='R',a--;
				else if(b>0) ans[i]='P',b--;
				else ans[i]='S',c--;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

# [CF1245B Restricted RPS](https://www.luogu.com.cn/problem/CF1245B)
贪心呗，谁还贪得过你啊！

很容易想出，能赢就尽量赢，然后如果没法赢过 $\left\lceil\dfrac{n}{2}\right\rceil$ 次的话，~~进厂吧~~，就输了，如果赢了，那么后面剩下的游戏次数随便出就行了。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
int T,n,a,b,c;
string x;
int main(){
	cin>>T;
	while(T--){
		string ans;
		cin>>n>>a>>b>>c>>x;
		ans.resize(n);
		int cnt=0;
		for(int i=0;i<n;i++)
			if(x[i]=='S')
			{	 if(a>0) a--,ans[i]='R',cnt++;}
			else if(x[i]=='R')
			{	 if(b>0) b--,ans[i]='P',cnt++;}
			else if(c>0) c--,ans[i]='S',cnt++;
		if(cnt>=(n+1)/2){
			cout<<"YES"<<endl;
			for(int i=0;i<n;i++)
				if(ans[i]!='R' && ans[i]!='P' && ans[i]!='S')
					if(a>0) ans[i]='R',a--;
					else if(b>0) ans[i]='P',b--;
					else ans[i]='S',c--;
			cout<<ans<<endl;
		}
		else cout<<"NO"<<endl;
	}
	return 0;
}
```
感谢管理员审核，感谢读者阅读！

---

## 作者：jess1ca1o0g3 (赞：0)

当可以使用的时候就使用，填上对应的字符。

如果不能用，就随便选一个填上。

如果赢得的次数 $k$ 满足 $2k<n$ 那就赢不了。

注意对应关系，很容易混淆。

[Code](https://paste.ubuntu.com/p/J8Rfywwc9c/)。

---

## 作者：Crasole (赞：0)

## 题意

给出一个长度为 $n$ 的字符串 $s$，$s$ 只有 $R , P , S$ 三个字符组成，$R$ 代表石头，$P$ 代表布，$S$ 代表剪刀，字符串 $s$ 代表对手出手势的顺序。现在给出 $a , b , c$ 三个数，分别代表能出 $a$ 次石头、$b$ 次剪刀、$c$ 次布。

现在问：能否安排自己的出手势的顺序，使得自己赢得对手，赢得条件是自己至少击败了对手 $\lceil \frac{n}{2} \rceil$ 次（向上取整）。

如果自己赢了，则输出 `YES`，并输出方案（如果有多种，则输出任意一种）。否则输出 `NO`。

一共有 $T$ 组数据

## 思路

对于每一次的输入，如果能赢，就出。如果赢不了，则随便输出一个。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,st,jd,bu;
char s1[110],s2[110];//s1读入，s2方案
int main(){
	cin>>T;
	while(T--){
		memset(s2,0,sizeof(s2));//清空
		cin>>n>>st>>bu>>jd;
		int cnt=0;
		scanf("%s",s1);
		for(int i=0;i<n;i++)//先把能出的出了
			if(s1[i]=='R'&&bu)
				--bu,++cnt,s2[i]='P';
			else if(s1[i]=='P'&&jd)
				--jd,++cnt,s2[i]='S';
			else if(s1[i]=='S'&&st)
				--st,++cnt,s2[i]='R';
		if(cnt>=ceil(n/2.0)){//胜负判定
			cout<<"YES\n";
			for(int i=0;i<n;i++)//不能出的随便出
				if(!s2[i]){
					if(st){
						st--;cout<<"R";
					} 
					else if(jd){
						jd--;cout<<"S";
					} 
					else if(bu){
						bu--;cout<<"P";
					} 
				}
				else cout<<s2[i];
			cout<<endl;
		}
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

暴力构造:  
能赢的全部都填上  
不能赢的对结论没有影响,所以随便填  
```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 123;
char s1[N], s2[N];


int main() {
	int t, pa, pb, pc, cnt, n;
	scanf("%d", &t);
	while(t--) {
		memset(s2, 0, sizeof(s2));
		cnt = 0;
		scanf("%d %d %d %d %s", &n, &pa, &pb, &pc, s1);
		int len = strlen(s1);
		for(int i = 0; i < len; ++i) {
			if(s1[i] == 'R') {
				if(pb) {
					--pb; s2[i] = 'P'; ++cnt;
				}
			} else if(s1[i] == 'P') {
				if(pc) --pc, s2[i] = 'S', ++cnt;
			}
			else if(s1[i] == 'S') {
				if(pa) --pa, s2[i] = 'R', ++cnt;
			}
		}
		if((n + 1) / 2 <= cnt) {
			printf("YES\n");
			for(int i = 0; i < n; ++i) {
				if(!s2[i]) {
					if(pa) --pa, s2[i] = 'R';
					else if(pb) --pb, s2[i] = 'P';
					else --pc, s2[i] = 'S';
				}
			}
			printf("%s\n", s2);
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：wubaiting2020 (赞：0)

直接照题意模拟  
#### 1.首先先将能赢的个数计算出来  
#### 2.判断每种手势多了多少个  
#### 3.把不能赢的用多的手势填上  
注意下多组数据的初始化和各个手势不要搞混了就行


------------
代码 

```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
using namespace std;
int read()
{
   int s=0,bj=0;
   char ch=getchar();
   while(ch<'0'||ch>'9')bj|=(ch=='-'),ch=getchar();
   while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
   return bj?-s:s;
}
void printnum(int x)
{
	if(x>9)printnum(x/10);
	putchar(x%10^48);
}
void print(int x,char ch)
{
	if(x<0){putchar('-');x=-x;}
	printnum(x);putchar(ch);
}
int T;
int a,b,c,n;
char ch[105];
int bj1,bj2,bj3;
int num1,num2,num3;
int m1,m2,m3;
int main()
{
	T=read();
	while(T--)
	{
		n=read();bj1=bj2=bj3=0;//多组数据注意初始化 
		a=read();b=read();c=read();
		scanf("%s",ch+1);
		for(int i=1;i<=n;i++)
		if(ch[i]=='R')bj1++;
		else if(ch[i]=='P')bj2++;
		else bj3++;//算出对手每种手势出了多少个 
		num1=min(bj1,b);num2=min(bj2,c);num3=min(bj3,a);//对手出R/P/S时我能赢的局数 
		m1=a-num3;m2=b-num1;m3=c-num2;//R/P/S多的手势数 
		if(num1+num2+num3>=n/2+n%2)//如果超过了(n/2)(向上取整) 
		{
			puts("YES");
			for(int i=1;i<=n;i++)
			if(ch[i]=='R')
			{
				if(num1){num1--;putchar('P');}//能赢的赢 
				else
				{
					if(m1){m1--;putchar('R');}
					else if(m3){m3--;putchar('S');}//不能赢的随便选一个 
				}
			}
			else if(ch[i]=='P')//同上 
			{
				if(num2){num2--;putchar('S');}
				else
				{
					if(m1){m1--;putchar('R');}
					else if(m2){m2--;putchar('P');}
				}
			}
			else//同上 
			{
				if(num3){num3--;putchar('R');}
				else
				{
					if(m2){m2--;putchar('P');}
					else if(m3){m3--;putchar('S');}
				}
			}
			puts("");
		}
		else puts("NO");//小于(n/2)(向上取整)输出NO 
	}
	return 0;
}

``


---

