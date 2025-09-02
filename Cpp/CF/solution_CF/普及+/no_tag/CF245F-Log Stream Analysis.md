# Log Stream Analysis

## 题目描述

现在给你一份日志，有若干行，每一行由`2012-月-日 时:分:秒:日志信息`，时间为24小时计时法，日志信息中可能会有空格。你的任务是找出第一个往前n秒中有不少于m条日志的在日志里的时刻。

## 样例 #1

### 输入

```
60 3
2012-03-16 16:15:25: Disk size is
2012-03-16 16:15:25: Network failute
2012-03-16 16:16:29: Cant write varlog
2012-03-16 16:16:42: Unable to start process
2012-03-16 16:16:43: Disk size is too small
2012-03-16 16:16:53: Timeout detected
```

### 输出

```
2012-03-16 16:16:43
```

## 样例 #2

### 输入

```
1 2
2012-03-16 23:59:59:Disk size
2012-03-17 00:00:00: Network
2012-03-17 00:00:01:Cant write varlog
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 2
2012-03-16 23:59:59:Disk size is too sm
2012-03-17 00:00:00:Network failute dete
2012-03-17 00:00:01:Cant write varlogmysq
```

### 输出

```
2012-03-17 00:00:00
```

# 题解

## 作者：HyGeoIceFairy (赞：2)

其实我刚看到这题就想到轮换着保存数据，结果调了好久……太蒻了……
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

string t;
long long te;
queue <string> q;
int m,n;
int month[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};//每月天数，2012年是闰年
long long cha(string d)
{
	int mo=(d[5]-'0')*10+d[6]-'0';
	int da=(d[8]-'0')*10+d[9]-'0';
	int ho=(d[11]-'0')*10+d[12]-'0';
	int mi=(d[14]-'0')*10+d[15]-'0';
	int se=(d[17]-'0')*10+d[18]-'0';
	for(register int i=1;i<=mo-1;++i)
	{
		da+=month[i];
	}
	return da*86400+ho*3600+mi*60+se;
}//将字符串转换成秒
int main()
{
	scanf("%d%d",&n,&m);
	getchar();//吸回车
	while(getline(cin,t))
	{
		te=cha(t);
		while(!q.empty()&&(te-cha(q.front()))>=n)//这里用到队列，符合当前条件数据就保留
		{
			q.pop();
		}//将不属于n秒内的数据统统去掉
		if(q.size()>=m-1)//符合条件就直接输出，保证最早
		{
			for(register int i=0;i<=18;++i)
			{
				printf("%c",t[i]);
			}
			return 0;
		}
		q.push(t);
	}
	printf("-1");//没有符合条件就输出-1
	return 0;
}
```
后记：这代码洛谷上RemoteJudge出UKE，但是实际上CodeForce里却是AC，真奇怪……

---

## 作者：leo120306 (赞：1)

终于 A 了这道题，不容易啊。

~~（点进这道题之前它还是黄的呢，怎么突然绿了？是我眼花了吗？）~~
## 思路
模拟即可。首先把一行里的数字都读出来，全部压进一个 long long。因为日志信息里没有数字，所以可以少判很多。然后滑动窗口进行判断，因为日志时间有序，所以令窗口大小为 $m$，只需判断首尾之差是否大于 $n$ 即可。求差最麻烦了，要注意：
- 全部是 2012 年的日志，而 2012 年是个闰年。
- 求一天在一年中是第几天时，月份要预处理前缀和。
- 变量名不要打错。

然后就是码代码时间了。

## 实现
别看它很长，有一大半都是在读写。
```cpp
#include <cstdio>
using namespace std;
#define ll long long
#define ull unsigned long long

namespace io{
const int size=(1<<20)+1;
char buf[size],*p1=buf,*p2=buf;
char buffer[size];
int op1=-1;
const int op2=size-1;
inline char readchar() {
	if(p1!=p2) {
		return *p1++;
	}
	return p1==(p2=(p1=buf)+fread(buf,1,size-1,stdin))?EOF:*p1++;
}
inline void flush() {
	fwrite(buffer,1,op1+1,stdout),op1=-1;
}
inline void writechar(const char &x) {
	if(op1==op2) flush();
	buffer[++op1]=x;
}
#ifndef ONLINE_JUDGE
#define gc getchar
#else
#define gc readchar
#endif
#define pc writechar
#define el pc(10)
#define sp pc(32)
inline int readi(){
	int x=0;bool w=0;
	char ch=gc();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc();
	}
	return w?-x:x;
}

inline ll readull(){
	ll x=0;
	char ch=gc();
	while(ch>=32){
		if(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48);
		ch=gc();
	}
	if(ch==-1) x=-x;
	return x;
}

void writei(int x){
	if(x<0) pc('-'),x=-x;
	if(x>9) writei(x/10);
	pc((x%10)^48);
}
};// io
using namespace io;

const int months[]={0,31,29,31,30,31,30,31,31,30,31,30,31},
pre[]={0,31,60,91,121,152,182,213,244,274,305,335,366};
inline ll td(ll x,ll y){
	int xm=x/100000000%100,ym=y/100000000%100;
	int xd=pre[xm-1]+x/1000000%100,yd=pre[ym-1]+y/1000000%100;
	int xh=x/10000%100,yh=y/10000%100;
	int xmi=x/100%100,ymi=y/100%100;
	int xs=xh*3600+xmi*60+x%100,ys=yh*3600+ymi*60+y%100;
	return (0ll+xd)*86400+xs-((0ll+yd)*86400+ys);
}

ll a[50005];
int main(){
	int n=readi(),m=readi();
	int cnt=0;
	while((a[++cnt]=readull())>0);
	if(a[cnt]==0)cnt--;
	else a[cnt]=-a[cnt];
	for(int i=0;i<=cnt-m;i++){
//		writel(td(a[i+m],a[i+1]));el;
		if(td(a[i+m],a[i+1])<n){
			#define i i+m
			writei(2012);pc('-');
			pc(a[i]/1000000000%10^48);
			pc(a[i]/100000000%10^48);
			pc('-');
			pc(a[i]/10000000%10^48);
			pc(a[i]/1000000%10^48);
			sp;
			pc(a[i]/100000%10^48);
			pc(a[i]/10000%10^48);
			pc(':');
			pc(a[i]/1000%10^48);
			pc(a[i]/100%10^48);
			pc(':');
			pc(a[i]/10%10^48);
			pc(a[i]%10^48);
			el;
			flush();
			return 0;
			#undef i
		}
	}
	writei(-1);
	flush();return 0;
} 
```

---

## 作者：lizhixun (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF245F)

### $\texttt{Description}$

给定两个整数 $n$ 和 $m$ 以及若干行日志，要求找出第一个在前 $n$ 秒内有 $m$ 条日志且被日志记载过的时刻。如果没有输出 $-1$ 即可。

### $\texttt{Solution}$ 

这题可以用队列来做，把表示的秒数存入队列，查找时就把不符合条件的全部删除掉，最后判断队列的长度是否符合要求，如果符合，就输出日志前面的时间。

至于时间怎么算，就不用多说了，直接看代码里面的模拟。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
string s;
queue<string> q;

const int Month[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int times(string s) {
	int month = (s[5] - '0') * 10 + s[6] - '0';
	int day = (s[8] - '0') * 10 + s[9] - '0';
	int hour = (s[11] - '0') * 10 + s[12] - '0';
	int minute = (s[14] - '0') * 10 + s[15] - '0';
	int second = (s[17] - '0') * 10 + s[18] - '0';
	
	for (int i = 1; i < month; i++) day += Month[i];
	return day * 86400 + hour * 3600 + minute * 60 + second;
}

// 字符串转秒数

signed main() {
	cin >> n >> m;
	getchar(); // 读入回车
	
	while (getline(cin, s)) {
		int tms = times(s);
		while (q.empty() == false && (tms - times(q.front())) >= n) q.pop();
		// 将不符合条件的全部删去
		if (q.size() >= m - 1) {
			cout << s.substr(0, 19);
			return 0;
		}
		// 判断是否满足条件
		q.push(s);
		// 存入队列
	}
	
	cout << -1 << endl;
	// 不符合条件，输出 -1
	return 0;
}
```

---

## 作者：Ferm_Tawn (赞：1)

此题实际难度为黄题(~~水死了~~)。

面对复杂的输入，我们可以读入字符串后在提取每个元素。

提取出来后，可以用 $sec$ 变量来统计从 ```2012:0:0 0:0:0``` 到每条指令所花费的秒数，这样可以将很多元素变成一个元素，在后面比较时较为方便。

$sec$ 变量的统计方法（按照日常的进制转换）：

- $1$ 分钟 $ = 60$ 秒

- $1$ 小时 $ = 60 \times 60 = 3600$ 秒
- $1$ 天 $ = 60 \times 60 \times 24 = 86400$ 秒
- $1$ 个月 $ = $ 月份的天数 $  \times$ $86400$  秒

接下来，遍历数组，找到第一个与最后一个元素相差$n$秒的元素下标$head$，然后检查 $head$ 与数组最后一个元素之间是否相差 $\ge m$ ，如果满足，则直接输出第  $head$ 条指令。

小坑点：

- 由于题目给出的年份是闰年，月份数组中的二月份应为$29$天

你们的代码(~~别只看代码~~)：

```cpp
#include<bits/stdc++.h>
using namespace std;
int mon[15] = {0 , 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 32};//月份数组 
string s;
vector<int> v; 
int n , m , head;
int input(string temp){//字符串转整数，模板 
	int val;
	stringstream sin;
	sin << temp;
	sin >> val;
	return val;
}
int main(){
	cin >> n >> m;
	getline(cin , s);
	while(getline(cin , s)){
		//使用字串的方式提取 
		int month = input(s.substr(5 , 2));
		int day = input(s.substr(8 , 2));
		int hour = input(s.substr(11 , 2));
		int minute = input(s.substr(14 , 2));
		int second = input(s.substr(17 , 2));
		int sec = second + minute * 60 + hour * 3600 + day * 24 * 3600;//求出多少秒 
		for(int i = 1 ; i < month ; i++) sec += mon[i] * 24 * 3600;//加上月份的秒数 
		while(head < v.size() && v[head] + n <= sec) head++;//寻找符合要求的下标 
		v.push_back(sec);
		if(v.size() - head >= m){//如果满足要求，直接输出 
			cout << s.substr(0 , 19);
			return 0;
		}
	}
	cout << -1 << endl;//否则无解 
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

考虑模拟。

看到这种题目，我们可以直接采取用队列维护的做法，将每一条日志所代表的秒数计算出来，将其放入队列中，如果队头元素与现在时间的差大于了我们输入的 $n$，说明这条日志应该被清理了，就将其移出队列。

在每一条日志放入队列后，就可以判断是否长度大于等于 $m$，如果大于等于了，就说明此时完成任务，输出答案，否则在最后输出 $-1$。

给出带注释的代码：
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
queue<int> q;//队列
string s,t;
int n,m;
int runnian(int s)//计算年份的天数
{
	if(s%100!=0&&s%4==0)return 366;
	else if(s%400==0)return 366;
	else return 365; 
}
int month(int u,int s)//计算月份的天数
{
	int cnt=0;
	while(u)
	{
		if(u==1||u==3||u==5||u==7||u==8||u==10||u==12)cnt+=31;
		else if(u==4||u==6||u==9||u==11)cnt+=30;
		else
			if(runnian(s)==366)cnt+=28;
			else cnt+=29;
		u--;
	} 
	return cnt;
}
int qianyiduan(string tmp)//计算年月日所代表的秒数
{
	int us=0;
	int year=0,idx1=0,idx2=0,cnt=0;
	for(int i=0;i<tmp.size();i++)
		if(tmp[i]=='-') break;
		else if(tmp[i]<='9'&&tmp[i]>='0') year=year*10+tmp[i]-'0',idx1++;
	us+=runnian(year)*24*60*60,idx2=idx1+1;
	for(int i=idx1+1;i<tmp.size();i++)
		if(tmp[i]=='-') break;
		else if(tmp[i]<='9'&&tmp[i]>='0') cnt=cnt*10+tmp[i]-'0',idx2++;
	us+=month(cnt,year)*24*60*60,cnt=0;
	for(int i=idx2+1;i<tmp.size();i++)
		if(tmp[i]=='-') break;
		else if(tmp[i]<='9'&&tmp[i]>='0') cnt=cnt*10+tmp[i]-'0';
	us+=cnt*24*60*60;
	return us;
}
int houyiduan(string t)//计算时分秒所代表的秒数
{
	int us=0;
	int year=0,idx1=0,idx2=0,cnt=0;
	for(int i=0;i<t.size();i++)
		if(t[i]==':') break;
		else if(t[i]<='9'&&t[i]>='0') year=year*10+t[i]-'0',idx1++;
	us+=year*60*60,idx2=idx1+1;
	for(int i=idx1+1;i<t.size();i++)
		if(t[i]==':') break;
		else if(t[i]<='9'&&t[i]>='0') cnt=cnt*10+t[i]-'0',idx2++;
	us+=cnt*60,cnt=0;
	for(int i=idx2+1;i<t.size();i++)						
		if(t[i]==':') break;
		else if(t[i]<='9'&&t[i]>='0') cnt=cnt*10+t[i]-'0';
	us+=cnt;
	return us;
}
string uuu;
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	getline(cin,s);
	while(getline(cin,s))
	{
		string tmp,ans1;
		int idx1=0;
		for(int i=0;i<s.size();i++)
			if(s[i]==' ')break;
			else tmp+=s[i],idx1++;
		int ans=qianyiduan(tmp);
		ans1=tmp;
		tmp="";
		for(int i=idx1+1;i<s.size();i++)
			if(s[i]>='A'&&s[i]<='Z'||s[i]<='z'&&s[i]>='a')break;
			else tmp+=s[i],idx1++;
		ans+=houyiduan(tmp); 
		q.push(ans);
		while(ans-q.front()>=n&&!q.empty()&&q.size()>1)q.pop();
		if(q.size()>=m&&uuu=="") uuu=ans1+" "+tmp;
	}
	if(uuu!="")cout<<uuu<<endl;//输出答案
	else cout<<-1<<'\n';//没有答案，输出-1
	return 0;
}
```

---

## 作者：ArcherHavetoLearnWhk (赞：0)

较简单的模拟。

#### 思路：
输入字符串时可以通过字符串操作计算出时刻距离 ```2012:0:0 0:0:0``` 的时间戳简化比较过程。

并且通过队列维护目前时间前 $n$ 秒内的所有时间戳，每次新时间戳进队并将 $n$ 秒前之前的所有时间戳弹出队列，此时一旦队里有不少于 $m$ 条时间戳即输出并结束。

#### 代码：（一些技巧和点在注释里）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,mth[]={0,31,60,91,121,152,182,213,244,274,305,335,366};//前缀和数组更加方便，注意闰年二月29天
queue<int>q; 
string s;
int snum(string str){//字符串转数字 
	int res=0,len=str.size();
	for(int i=0;i<len;i++)
		res=res*10+(str[i]&15);//这里位运算很巧，等价于str[i]-'0'，提速 
	return res;
}
int cal(string str){//计算时间戳
	int d=snum(s.substr(8,2))+mth[snum(s.substr(5,2))-1];//substr函数比较方便
	return d*86400+snum(s.substr(11,2))*3600+snum(s.substr(14,2))*60+snum(s.substr(17,2));
}
int main(){
	cin>>n>>m;
	getchar();//getchar读走回车避免getline出错
	while(getline(cin,s)){
		int t=cal(s);
		q.push(t); 
		while(!q.empty()&&t-n>=q.front())q.pop();
		if(q.size()>=m){//发现满足的就直接输出并结束
			cout<<s.substr(0,19);
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

这也配成为 $2000$ 的难度？

思路，直接模拟，~~相信各位都做过儒略日把，那道题目正好和这道是反一反。~~，找一个参照的时间，然后将当前这个时间减去那个参照的时间，转成秒。

这样就可以很方便的比较大小以及可以直接减去 $n$ 秒。

当然，这样处理完之后，我们还是不能很迅速的得出答案，我们发现这个消息的条数有 $5 \times 10^6$，显然需要一个线性的做法。

一开始我想到的是，搞出来一个时间之后，可以直接二分，然而这肯定会 TLE 起飞。

于是我们发现这个时间具有单调性，那么我们所维护的区间也是具有单调性，因为区间的长度不变。

维护这种类型的题目，我们经常用到双指针来做到线性，用一个 $l$ 来表示当前可以扩张到最小的左边是哪里，然后我们发现这个 $l$ 肯定是只增不减，这样子的话就可以做到均摊意义下是线性的。

我处理第一部分内容的时候，可能稍微有点小技巧，比如 $3$ 月 $14$ 日 $12$ 点，我是直接将 $14$ 天给算完了，这样相当于将每一个信息都平移了 $1$ 天，所以不会出现问题。

当然，如果你很吃的空，把日子减一减然后再把月份减一减我拦不了你。

另外注意 $2012$ 可是一个闰年哦。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=5e6+5;
const int m1[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int n,m,aa[INF],tot;
string s1;
int f() {
    int xx=0;
    xx+=(s1[17]-'0')*10+(s1[18]-'0');
    xx+=((s1[14]-'0')*10+(s1[15]-'0'))*60;
    xx+=((s1[11]-'0')*10+(s1[12]-'0'))*60*60;
    xx+=((s1[8]-'0')*10+(s1[9]-'0'))*60*60*24;
    int kk=(s1[5]-'0')*10+(s1[6]-'0');
    for (int i=1;i<kk;i++)
        xx+=m1[i]*60*60*24;
    return xx;
}
signed main()
{
    scanf("%lld %lld ",&n,&m);int l=1;
    while (getline(cin,s1)) {
        int ll=f();
        aa[++tot]=ll;
        // cout<<ll<<"\n";
        while (aa[l]<=aa[tot]-n) l++;
        if (tot-l+1>=m) {
            for (int i=0;i<=18;i++)
                cout<<s1[i];
            cout<<"\n";
            return 0;
        }
    }
    cout<<"-1\n";
    return 0;
}
```


---

