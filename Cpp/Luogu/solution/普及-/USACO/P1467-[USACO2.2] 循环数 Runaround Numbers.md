# [USACO2.2] 循环数 Runaround Numbers

## 题目描述

循环数是那些不包括 $0$ 且没有重复数字的整数（比如 $81362$）并且还应同时具有一个有趣的性质, 就像这个例子:

如果你从最左边的数字开始（在这个例子中 $8$）向右数最左边这个数（如果数到了最右边就回到最左边），你会停止在另一个新的数字（如果停在一个相同的数字上，这个数就不是循环数）。  

就像：$8\ 1\ 3\ 6\ 2$ 从最左边接下去数 $8$ 个数字: $1\ 3\ 6\ 2\ 8\ 1\ 3\ 6$ 所以下一个数字是 $6$

重复这样做 (这次从 `6` 开始数 $6$ 个数字) 并且你会停止在一个新的数字上: $2\ 8\ 1\ 3\ 6\ 2$, 也就是 $2$

再这样做 (这次数两个): $8\ 1$

再一次 (这次一个): $3$

又一次: $6\ 2\ 8$   

这时你回到了起点,在经过每个数字一次后回到起点的就是循环数。如果你经过每一个数字一次以后没有回到起点, 你的数字不是一个循环数。

给你一个数字 $m$ ，找出第一个比 $m$ 大的循环数, 输出数据保证结果能用一个无符号长整型数 $ \in [0,2^{32})$ 装下。 （追加提醒：循环数每个数位都必须要访问到）


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le m \le 10^9$。

翻译来自NOCOW

USACO 2.2


## 样例 #1

### 输入

```
81361
```

### 输出

```
81362
```

# 题解

## 作者：Ambtion (赞：18)

千万要记住while(1)
不要while(n)

不然会t的

暴力＋剪枝
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int b[200],l,visit[200],a[200];
int zhuan(int x)
{
	int t=0;
	while(x>0)
	{
		b[++t]=x%10;
		x/=10;
	}
	for(int i=1;i<=t;++i)a[i]=b[t-i+1];//逆序存进去 
	return t;//长度 
}
bool you()
{
	int t=1;//开始的位置 
	memset(visit,0,sizeof visit);//每一次都memset一遍 
	for(int i=1;i<=l;++i)
	{
		if(visit[a[t]]||a[t]==0)return 0;//走过就会有环;零也不行; 
		visit[a[t]]++;//走过了; 
		t=(t+a[t])%l;//走到下一位上; 
		if(t==0)t=l;//最后一个就是l; 
	}
	if(t!=1)return 0;//没走到原来的辣个位置当然就"挂了"; 
	return 1;
}
int main()
{
	int ok;
	scanf("%d",&ok);
	while(233)
	{
		ok++;
		l=zhuan(ok);
		if(you())
        {
        	printf("%d",ok);
     	   return 0;
        }
	}
	return 0;
}
```

---

## 作者：Makasukaka (赞：9)


我们不暴力枚举每一个数，然后验证它是否满足条件。我们反
而考虑如何构造这个数。

考虑到每一位的变化其实是与当前这位数和总位数有关的，所以我们枚举总位数从1到9，然后枚举每一位可以填什么数，以及下一位是否指向一个空位。

注意如果你当前所填的是最后一个位，那么你一定要让其指向第一位。

满足条件的数其实是很有限的。。。

具体的看代码。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int used[10],pla[10],ans[1000005],tot;
inline void add(int up){
    int res=0,f=0;
    for(int i=1;i<=up;++i){//判断0的存在
    	if(!pla[i])f=1;
    	res=res*10+pla[i];
    }
    if(!f)ans[++tot]=res;
}
inline void dfs(int pos,int x,int up){
    //printf("%d %d %d\n",pos,x,up);
    if(x>up){add(up);return ;}
    for(int i=1;i<=9;++i){
        if(!used[i]){
            int nxt=(pos-1+i)%up+1;
            if(x!=up){//如果不是最后一位
               if(!pla[nxt]){//指向一个空位，可以填
                    pla[pos]=i;
                    used[i]=1;
                    dfs(nxt,x+1,up);
                    pla[pos]=0;
                    used[i]=0;
               }
            }
            else{
                if(nxt==1){//指向首位，可以填
                    pla[pos]=i;
                    used[i]=1;
                    dfs(nxt,x+1,up);
                    pla[pos]=0;
                    used[i]=0;
                }
            }
        }
    }
}
int main(){
    int x;scanf("%d",&x);
    for(int i=1;i<=9;++i){
        dfs(1,1,i);
    }
    sort(ans+1,ans+1+tot);
    for(int i=1;i<=tot;++i){
        if(ans[i]>x){
            printf("%d\n",ans[i]);
            break;
        }
    }
    return 0;
}

```


---

## 作者：BlueArc (赞：7)

枚举框架:

```cpp
for(int i=n+1;;i++)
{
 int ok=1;
 1.if(i中有0) ok=0;
 2.if(i中有重复数字) ok=0;
 3.if(按规则走到一个已走过的位置) ok=0;
 if(ok) 输出i，退出 
}
```
1，2只要数字转成字符就很好判
char s[25];

sprintf(s,"%d",i);(i是数字)

虽然stringstream 也可以，但...是真的慢

 
关键的3:

走到下一个位置:(0是起点)

nxt=(now+s[now]-'0')%len; (当前位置+步数)膜一下就行了

```cpp
/#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
int vis[20];
int main()
{
 int n;
 cin>>n;
 for(int q=n+1;;q++)//暴力尝试 
 {
  memset(vis,0,sizeof(vis));//vis判是否有重复数字，新数清0 
  char s[25];
  sprintf(s,"%d",q);//转成字符串,stringstream要慢好多 
  int len=strlen(s); 
  int ok=1;
  for(int j=0;j<len;j++) if(s[j]=='0') ok=0;//题目说的不包括0
  if(!ok) continue;//不行的话下一个数尝试 
  for(int j=0;j<len;j++)
   {
    int num=s[j]-'0';
    if(vis[num]) {ok=0;break;}
    vis[num]=1;
```
}//题目说的无重复数字
   
```cpp
  if(!ok) continue;
  int now=0;//当前走到了哪个位置(第0,1,2,3...len(n)-1)
  memset(vis,0,sizeof(vis));//资源利用，再来判是否到了一个新的位置 
  vis[0]=1;
  for(int j=0;j<len-1;j++)//除掉第一次还有len-1次 
  {
   int nxt=(now+s[now]-'0')%len;//走到的下一个位置 
   if(vis[nxt]) {ok=0;break;}//不是新位置 
   vis[nxt]=1;
   now=nxt; 
  }
  int nxt=(now+s[now]-'0')%len;//最后一次 
  if(nxt!=0) ok=0;//必须是起点0 
  if(ok) {cout<<q<<endl;return 0;}
 }
 return 0;
}

```

---

## 作者：pengym (赞：5)

主思路是先判断有没有重复的数字，其次是模拟题目中循环的过程，不多说，重要代码注释在代码中。下附代码：


```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int m;
int cc(int x)    //判断是否有重复的数字 
{
    int js[15]={0};//统计出现次数 
    int a[25]={0};//存放每一位数字 
    int w=1;
    while(x>0)
    {
        a[w]=x%10;
        w++;
        x/=10;
```
}//分离并储存每一位


```cpp
    w--;
    for(int i=1;i<=w;i++)
    {
    if(js[a[i]]==1)return 0;//如果重复，则不符合 
    if(js[a[i]]==0)js[a[i]]=1;
    }
    return 1;//没有重复的数字 
}
int fun(int x)//纯模拟 
{
    int a[25]={0};//存放每一位数字
    int b[25]={0};//模拟循环顺序 
    int c[25]={0};//记录是否每一位都访问 
    int w=1;
    while(x>0)
    {
        a[w]=x%10;
        w++;
        x/=10;
    }
    int s=--w;  //作用同上一个cc  
                //S做下标 
    for(int i=1;i<=w;i++,s--)
    {
    b[i]=a[s];
    c[i]=a[s];//记录每一位
```
}//将数字正序 int next=b[1],first=next;//first记录最开始访问的数，next指示下一个数

```cpp
    int dq=1;//当前下标 
    s=w;
    while(s>0)//循环每一个数 
    {
        if(next+dq<=w)//如果不会超过数组长度，直接到下一个数 
        {
            s--;
            c[dq]=-1;//标记已访问 
            dq=next+dq;//下标变换 
            next=b[dq];
        }
        else
        if(next+dq>w)//如果超过长度，循环处理 
        {
            s--;
            c[dq]=-1;
            dq=next+dq;    
            if(dq%w==0)dq=w;//循环下标 
            else dq%=w;
            next=b[dq];                
        }    
    }
    for(int i=1;i<=w;i++)
    if(c[i]!=-1)return 0;//判断全部访问 
    if(first==next)return 1;//判断最开始的数与最后一个数相同 
    return 0;
}
int main()
{
    scanf("%d",&m);
    while(1)
    {
        m++;    //一个个枚举 
        if(cc(m)&&fun(m))
        {
            cout<<m;//输出 
            break;//直接退出 
        }
    }
    return 0;
}
```

---

## 作者：Numenor (赞：3)

### 爆搜直接干，这题题目难懂，细节还多，虽然思路简单，但是实现起来还是需要细心。
首先，我们暴力枚举数字，并判断其是否有0或重复的数字。接着进行爆搜。

边界为：

1.每一个数字都搜到了，如果当前在搜索起点，则可行，如果不在，则不可行。

2.如果一个数字被重复搜len次，（就像spfa判负环那样），那么说明陷入死循环，如：123456。直接关掉。
    下面贴code：
    
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
unsigned long long n;
int vis[10];
int a[30],len;

bool chk(int x)
{
	memset(vis,0,sizeof(vis));
	while(x)
	{
		if(vis[x%10]||x%10==0)return 0;
		vis[x%10]=1;x/=10;
	}return 1;
}

bool dfs(int x,int cnt)
{	
	if(vis[a[x]]==len)return 0;
	if(cnt==len+1)
	{
		if(a[x]==a[len])return 1;
		return 0;
	}
	if(!vis[a[x]])cnt++;
	vis[a[x]]++;
	int to=(x-(a[x]%len)+len)%len;
	if(to==0)to=len;
	return dfs(to,cnt);
}
	

bool f(int x)
{
	len=0;
	int cnt=0;memset(vis,0,sizeof(vis));
	while(x)
	{
		a[++len]=x%10;x/=10;
	}
	return dfs(len,1);
}

int main()
{
	cin>>n;
	while(1)
	{
		n++;
		if(!chk(n))continue;
		if(f(n)){cout<<n;return 0;}
	}
}		
```

    

---

## 作者：StaroForgin (赞：3)

本题还是一道十分基础的题，没什么说的，把每个比他大的数字都枚举一遍就行了。
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<set>
#include<map>
using namespace std;
long long len,m;
bool flag[20],vis[15];
int main()
{
	scanf("%lld",&m);
	while(m)
	{
		m++;//开始枚举
		memset(flag,false,sizeof(flag));//清空
		memset(vis,false,sizeof(vis));
		long long s=m,b[20]={},a[20]={};
		len=0;
		while(s)
		{
			len++;
			a[len]=s%10;
			s/=10;
		}//算出正着来的顺序
		bool have_0=false;//判断一下是否符合题意
		for(int i=0;i<len;i++)
		{
			if(vis[a[i+1]]||!a[i+1])//判断
			{
				have_0=true;
				break;
			}
			b[len-i]=a[i+1];//倒过来
			vis[a[i+1]]=true;//记录
		}
		if(have_0)
			continue;//退出当前值的计算
		long long findlen=b[1],last=1;
		while(!flag[last])
		{
			flag[last]=true;
			last=(last+findlen)%len;
			if(last==0)
				last=len;
			findlen=b[last];
		}//循环一遍
		if(last==1)
		{
			bool pl=false;
			for(int i=1;i<=len;i++)
				if(!flag[i])
				{
					pl=true;
					break;
				}//有无未遍历的
			if(pl)
				continue;
			printf("%lld",m);//输出
			return 0;//退出
		}
	}
	return 0;
}
```
主要是认真读题，条件很多！！！

---

## 作者：Fa1thful (赞：2)

### 算法：
暴力枚举  /  深度优先搜索dfs



#### 思路：

    因为每一位都要求是不一样的，故最多也只可能出现9位，故从给出的数 N 开始+1进行判断，对数数的方法进行模拟，方便数数并且标记，所以用 char 型数组存，以每个数为起点各数一次，保存每次数完后的结尾数，若这些结尾数构成的数刚好都包括了这个数的每一位数，则满足要求。

### 完整代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
char num[50], Cout[5], sum[50];
int temp[50], vis[10], e[10];
int test1()  //测试是否出现0且是否没有相同的数
{
    memset(vis,0,sizeof(vis));
    int len = strlen(sum);
    for (int i = 0; i < len; i++)
    {
        if(vis[sum[i] - '0']) return 0;
        if(sum[i] == '0') return 0;
        vis[sum[i] - '0'] = 1;
    }
    return 1;
}
int test2()  //测试每一位数是否都能在末尾出现过
{
    for (int i = 0; i < 10; i++)
    {
        if (vis[i])
        {
            if (!e[i]) return 0;
        }
    }
    return 1;
}
void plus_one()  //对数进行+1处理
{
    int len = strlen(num);
    int CIN = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        int ans;
        if (i == len - 1) ans = num[i] - '0' + 1 + CIN;
        else ans = num[i] - '0' + CIN;
        num[i] = ans % 10 + '0';
        CIN = ans / 10;
    }
    int len_out = 0;
    while (CIN)
    {
        Cout[len_out++] = CIN % 10 + '0';
        CIN /= 10;
    }
    int k = 0;
    len_out = strlen(Cout);
    for (int i = len_out - 1; i >= 0; i--)
    {
    	sum[k++] = Cout[i];
    }
    for (int i = 0; i < len; i++)
    {
    	sum[k++] = num[i];
    }
    sum[k] = '\0';
    return;
}
int main()
{
    int k, len, sta, end;
    cin >> num;
    while (1)
    {
        do
        {
            plus_one();
        } while (!test1());
        len = strlen(sum);
        memset(temp,0,sizeof(temp));
        memset(e,0,sizeof(e));
        k = 0;
        sta = 0;
        while (!temp[sta])   //统计末尾的数
        {
            temp[sta] = 1;
            int ans = sum[sta] - '0';
            while (ans > len)
            {
            	ans -= len;
	    }
            if (ans > len - (sta + 1)) end = ans - (len - sta - 1) - 1;
            else end = sta + ans;
            e[sum[end] - '0'] = 1;
            if (temp[end]) break;
            sta = end;
        }
        if (test2())
        {
            cout << sum << endl;
            break;
        }
    }
    return 0;
}
```


---

## 作者：MaverickT (赞：1)

蒟蒻的第一篇题解 ~~（水。。。~~

就是考审题


（1）不包括0且没有重复数字的整数  
（2）第一个比 M大

思路：

模拟，直接暴力判断

具体看代码


------------

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long m;//舍不得typedef你咬我？？？
int num[20],cnt=1,a[20];
int b[15]={0};
void get(long long x){//将位数取出来
	for(int i=0;i<=9;i++){//重置b[]
		b[i]=0;
	}
	cnt=1;
	while(x!=0){
		a[cnt]=x%10;
		x/=10;
		cnt++;
	}
	cnt--;
	memcpy(num, a, sizeof(num));//复制给num
	for(int i=1;i<=cnt;i++){//倒回来
		a[cnt-i+1]=num[i];
	}
}
bool keyi(long long x){
	get(x);
	for(int i=1;i<=cnt;i++){
		if(a[i]==0)return false;//要没有0
		b[a[i]]++;
	}
	for(int i=0;i<=9;i++){//要不重复
	if(b[i]>1)return false;
	b[i]=0;
	}
	int i=1,h=1;
	while(i<=cnt){//逐位判断
		int o=h;
		h=h+a[h];
		while(h>cnt){h-=cnt;}
		if(a[o]==a[h]){
			return false;
		}
		b[h]++;//神奇判断是否都遍历过
		i++;
	}
	int ans=0;
	for(int i=0;i<=9;i++){
		if(b[i]==1)ans++;
	}
	if(ans!=cnt){
		return false;
	}
	else
	return true;
}
int main() {
	cin>>m;
	m++;//要比原数大，就是这个地方多交了一次
	while(!keyi(m)){
		m++;
	}
	cout<<m;
	return 0;
}
//测试数据，好习惯
//99 147
//134259 134859
```


---

## 作者：EnderXie (赞：1)

简洁清奇的方法233~

首先说一下怎么判断循环数的：
```cpp
bool around(string n,char x,int pos){
	string str=n;
	while(str.size()<=x-'0'+pos)
		str+=str;//防止位数不够向后添位数
	char c=str[pos+x-'0'];//数到的数字
	_bs.set(n.find(c)),cnt++;//储存一下记录
	if(c==n[0]) return _bs.count()==n.size();//数了一个回环
	if(_bs.count()==n.size() || cnt==n.size()) return 0;//如果已经数了一遍，那么一定不是循环数
	return ((c=='0')?0:around(n,c,n.find(c)));//若c为0，也一定不是循环数
}
```

其他的有关判断重复数字的就不需要多说了吧？

注意我用到了to_string()与atoll()方法，所以要求开c++11。还有：题目要求询问**大于**输入的数的循环数，故每次应=先加一后判断。
那么直接上完整的代码：

```cpp
#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<b;i++)
#define ll unsigned long long
using namespace std;
string n;
bitset<10> _bs;
int cnt=0;
bool around(string n,char x,int pos){
	string str=n;
	while(str.size()<=x-'0'+pos)
		str+=str;
	char c=str[pos+x-'0'];
	_bs.set(n.find(c)),cnt++;
	if(c==n[0]) return _bs.count()==n.size();
	if(_bs.count()==n.size() || cnt==n.size()) return 0;
	return ((c=='0')?0:around(n,c,n.find(c)));
}
bool hasc(string n){
	bitset<10> bs;
	_for(i,0,n.size())
		if(!bs[n[i]-'0']) bs.set(n[i]-'0');
		else return 1;
	return 0;
}
int main(){
	cin>>n;
	while(true){
		n=to_string(atoll(n.c_str())+1);
		_bs.reset(),cnt=0;//重置记录
		if(!hasc(n) && around(n,n[0],0)) break;//找到答案了
	}
	cout<<n;
	return 0;
}
```

---

## 作者：QianhanOfficial (赞：1)

搜索思路:
从n+1开始搜索判断，用高精度分离每一位，然后进行递归模拟。  
本篇题解使用了set 用来判断是否存在重复数字，如果set大小和位数不同就返回假。   
顺便可以判断出是否存在0(输出set中最小的元素判断是否为0)  
STL的reverse可以把数列倒转过来 因为用了高精度所以需要倒转回正常顺序判断  
vis数组判断是否访问到了之前的数字。
```cpp
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define re register
using std::set;
using std::reverse;
set<int> ss;
int n, pos;
int a[23333];
bool vis[23333];
inline bool dfs()
{
	int j = 0;
	int s = pos + 1;
	reverse(a, a + s);
	for(re int i = 1; i <= s; ++i)
	{
		if(vis[j % s]) return false;
		else
		{
			vis[j % s] = true;
			j += a[j % s];
		}
	}
	if(j % s == 0) return true;
	return false;
}
bool judge(int x)
{
	memset(vis, false, sizeof(vis));
	ss.clear();
	a[0] = x;
	pos = 0;
	while(a[pos] >= 10)
	{
		a[pos + 1] = a[pos] / 10;
		a[pos] %= 10;
		++pos;
	}
	for(re int i = 0; i <= pos; ++i) ss.insert(a[i]);
	if((*ss.begin()) == 0 || ss.size() != pos + 1) return false;
	return dfs();
}
int main()
{
	scanf("%d", &n);
	while(true)
	{
		++n;
		if(judge(n))
		{
			printf("%d", n);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：maorui_cow (赞：1)

这道题我使用了字符串（感觉很方便），详细的介绍请看代码
```
#include<bits/stdc++.h>
using namespace std;
char a[20];
int l,bj[101],yd,ls[101];
long long n;//注意这里要用long long，不然放不下
int fz()//这里是一个转字符串的函数
{
	long long d=n;
	int x=0,y=0;
	memset(ls,0,sizeof(ls));//ls是一个临时数组，用来记录每一个数
	while(1)
	{
		ls[x]=d%10;
		x++;
		d/=10;
		if(d==0)
		{
			break;
		}
	}
	for(int i=x-1; i>=0; i--)//赋值
	{
		a[y]=ls[i]+48;
		y++;
	}
	l=y;//这里是长度赋值
}
int sp()//sp是用来判断数字是否重复的函数
{
	int x=0;
	memset(bj,0,sizeof(bj));
	for(int i=0; i<l; i++)
	{
		bj[a[i]-48]=1;//标记当前数字
	}
	for(int i=0; i<=9; i++)//这里只要到9是因为9是最大个位数
	{
		if(bj[i]==1)
		{
			x++;
		}
	}
	if(x!=l)//判断是否相等，因为如果有重复是绝对不会相等
	{
		return 0;
	}
	return 1;
}
int pd()//判断每一位是否都访问过
{
	int i;
	for(i=0; i<l; i++)
	{
		if(bj[i]==0)
		{
			return 0;
		}
	}
	return 1;
}
int dfs(int x)//这里就是深搜啦
{
	int y=((x+1)+(a[x]-48)-1);//这里用了一个优化
	if(bj[y-((y/l)*l)]==0)//直接求位置的优化
	{
		bj[y-((y/l)*l)]=1;//标记
		return dfs(y-((y/l)*l));
	}
	else
	{
		if((y-((y/l)*l))&&pd()==1)//判断是否为原点而且每个点都走过
		{
			puts(a);
			exit(0);
		}
		else
		{
			return 0;
		}
	}
}
int main()
{
	scanf("%lld",&n);
	while(1)
	{
		n++;
		memset(a,0,sizeof(a));
		fz();
		if(sp()==1)//这里的话放在前面更快
		{
			memset(bj,0,sizeof(bj));
			dfs(0);//深搜
		}
	}
	return 0;
}
```

//so easy!!

---

## 作者：whiteqwq (赞：1)

我们先从题目出发，要找到**各位不同**且**没有0**且从起始点开始，循环它的长度次后可以让每一个数字都**经过且只经过一次**，还要让起始点回到自己的位置上。

为什么没有0呢？ 我们想想，走到0上前进0步到达0，会无休止的循环，当然不行！

这句话听起来有点绕，我们以528为例：

从5出发，经过5个点，到达8，经过8个点，到达2，经过2个点，到达5

因为最后回到了起始点，且每个点都只经过一次。所以，我们可以证明，这个数字是循环数。

我们再举个栗子，来个长的：134859

1→3→5→8→9→4→1

完美！这个数是循环数！

所以，用伪代码表达就是

    for i=1 to 数字的长度
        if 当前位重复
            不行;
    for i=1 to 数字的长度
        if 未经过 且 当前位置不为0
            标记当前位置，将位置移动当前位置所表示的数的次数;
    for i=1 to 数字的长度
        if 未经过
            不行;
    if 初始点没有回来
        不行;
    else 可以;
        
下面是蒟蒻丑陋的代码：

各变量所表示：

i--循环量

n--输入的数字 

temp[]--暂时存储数字 

a[]--真正存储的数组 

p[]--判定数位是否重复 

b[]--判定各个数位是否经过 

s--数字长度 

loc--初始点

    #include<bits/stdc++.h>
    using namespace std;
    int i,n;
    int pd(int k){
        int temp[100],a[100],p[10]={0},b[100]={0},s=0,loc=1;
        while(k)
            temp[++s]=k%10,k/=10;
        for(int u=1;u<=s;u++)
            if(p[temp[u]])
                return 0;
            else p[temp[u]]++;
        for(int u=1;u<=s;u++)
            a[u]=temp[s-u+1];
        for(int u=1;u<=s;u++)
            if(b[loc]==0&&a[loc])
                b[loc]=1,loc=(loc+a[loc])%s==0? s:(loc+a[loc])%s;
        for(int u=1;u<=s;u++)
            if(b[u]==0)
                return 0;
        if(loc!=1)//切记要特判，蒟蒻就是在这WA了二次
            return 0;
        return 1;
    }
    int main()
    {	scanf("%d",&n);
        for(i=n+1;;i++)
            if(pd(i)){
                printf("%d",i);
                return 0;
            }
        return 0;
    }


---

## 作者：ylsoi (赞：1)

暴力解法，把这串数字转换为一个字符串，这样处理转换的时候就会方便的很多，每一次+1,模仿高精度加法一样地进位，但是要注意数中不可以有重复的数字，如果有重复的数字就可continue了

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=10+5;
char a[maxn];
int num[maxn],len;
bool vis[maxn],flag;
int main()
{
    scanf("%s",a);
    len=strlen(a);
    for(int i=0;i<len;i++)
    num[len-i]=a[i]^'0';
    while(!flag)//这个请忽略
    {
        num[1]++;
        for(int i=1;i<=len;i++)
        if(num[i]>=10)
        {
            num[i]-=10;
            num[i+1]+=1;
        }
        if(num[len+1])len++;
        memset(vis,0,sizeof(vis));
        int m;
        for(m=1;m<=len;m++)
        if(vis[num[m]])break;//这一步是判断有没有重复的数字
        else vis[num[m]]=1;
        if(m<len+1)continue;
        memset(vis,0,sizeof(vis));
        int cnt=0,k=len,i;
        for(i=1;i<=len;i++)
        {
            k=((k-num[k])%len+len)%len;
            if(vis[k])break;
            vis[k]=1;
        }
        if(i==len+1 && k==0)//如果又回到了起点，就可以输出了
        {
            for(int j=len;j>=1;j--)
            printf("%d",num[j]);
            cout<<endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：bjxdw (赞：1)

本人主要思路:每次判断一个数能不能成功，若能，输出，若不能，这个数+1继续判断，知道成功为止。

详细注释请见下面：|

|
\/

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[19],b[19],len,s[19],w[19];//a主要数组，b临时转换数组，len为a数组长度，s，w是计数器 
int change(unsigned long long x)
{
    int i,j,k,t,l=0;
    while(x>0)
    {
        b[++l]=x%10;
        x/=10;
    }
    for(i=1;i<=l;i++)
    {
        a[i]=b[l-i+1];//要b倒着输进a，因为b数组是倒的 
    }
    return l;//返回长度 
}
int check()
{
    int i,j,k=1,t=0;//k：当前位置  t：当前共走几步 
    memset(w,0,sizeof(w))，memset(s,0,sizeof(s));//初始化（其实只用一个数组就够了） 
    for(i=1;i<=len;i++)
    {
        if(w[a[i]]==1||a[i]==0)
            return 0;
        w[a[i]]++;
```
}//有重复数字，出现0----->直接return 0
```cpp
    while(t<len) 
    { 
        if(s[a[k]]>0)
            return 0;//若走过这个数，return 0 
        s[a[k]]++;//记录次数 
        t++;//更新t 
        k=(k+a[k])%len;//更新k 
        if(k==0)
            k=len;//可能出现k为0的情况 
    }
    if(k!=1)
        return 0;//若走完全部次数后未到1位，return 0 
    return 1;
}
int main ()
{
    int i,j,k;
    unsigned long long n;
    cin>>n;//输入 
    n++;//题目中说是大于，曾被坑 
    while(1)
    {
        len=change(n);//求这个数的长度并将数转化为数组 
        if(check()==1)
        {
            cout<<n;
            return 0;//大功告成，return 0 
        }
        n++;//不然继续往下搜 
    }
    return 0;
}
```

---

## 作者：我不是小明 (赞：1)


~~一道很水的模拟题（我却写了一个多小时，果然太弱了，汗-_-||）~~ 

就是将模拟其每一次最后一个到达的数，然后再进行一系列的判断

献上本人~~丑陋~~的代码。。~~（勿抄谢谢,否则您将成为作弊者。。）~~ 

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char c[1001];
int b[1001],l,num[1001];
int erro()//判断是否包含0，是否有重复的数字 
{
    int f[10];
    memset(f,0,sizeof(f));
    for(int i=0;i<l;i++)
        f[b[i]]++;
    if(f[0]>0)
        return 1;
    for(int i=1;i<=9;i++)
        if(f[i]>1)
            return 1;
    return 0;
} 
void work(int x)//将整数化成数组，为了后面好判断 
{
    int t=0;
    while(x!=0)
    {
        c[t]=(char)(x%10+48);
        x/=10;
        t++;
    }
}
int judge()//判断每一位上有没有多走 
{
    for(int i=0;i<l;i++)
        if(num[i]>1)
            return 0;
    return 1;
}
int judge2()//判断有没有走完 
{
    for(int i=0;i<l;i++)
        if(num[i]==0)
            return 0;
    return 1;
}
int main()
{
    long long n;
    cin>>n;
    while(n++)//一直循环找下一个 
    {
    	memset(num,0,sizeof(num));//清0 
        work(n);//化成逆序字符数组 
        l=strlen(c);
        for(int i=l-1;i>=0;i--)//化成顺序整型数组 
            b[l-i-1]=c[i]-48;
        if(erro())
            continue;
        int i=0,t=l,flag=1;
        num[i]++;
        while(judge())
        {
            if(b[(i+b[i])%l]==b[i])//判断到达的数字是否与当前数字相等 
            {
                flag=0;
                break;
            }
            i=(i+b[i])%l;//移位 
            num[i]++;//计数++ 
        }
        if(flag==1&&i==0&&judge2()){//输出 
            cout<<n;
            return 0;//提前直接解释程序 
        }
    }
    return 0;
}
```

---

## 作者：key_rA9 (赞：1)

[USACO2.2]Runaround Numbers【循环数】
直接从m+1搜索符合条件的数，用第i位的值加上i再对这个数的位数取余就是下一个位置。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int m,i,a[110],z;bool bk[110];
void num(int x)//数转成数组
{
	memset(a,0,sizeof(a));z=0;//有多少位
	while(x>0){a[++z]=x%10;x/=10;}//存数
	for(int i=1;i<=z/2;i++)swap(a[i],a[z-i+1]);//反转
}
bool pd(int x)
{
	num(x);memset(bk,0,sizeof(bk));//bk现在用来记录这个数是否出现过
	for(int i=1;i<=z;i++){if(bk[a[i]]||!a[i])return 0;bk[a[i]]=1;}//判相同数字，同时有0的话肯定不是循环数
	memset(bk,0,sizeof(bk));//再清空用来存是否找过
	int st=1,now=a[1]%z+1;//初始化，now记录现在位置
	while(1)
	{
		if(bk[now])//如果到了已经找过的数
		{
			for(int i=1;i<=z;i++)if(!bk[i])return 0;//有一个没有经过
			return 1;//除非全都找过否则就不是循环数
		}bk[now]=1;//遍历过了
		int next=(a[now]+now-1)%z+1;//求下一个的位置
		if(a[next]==a[now])return 0;//和上一个相同
		now=next;//跳到下一个
	}
}
int main()
{
	for(scanf("%d",&m),i=m+1;i<=2147483647;i++)//上界int，其实这里应该只需要搜到10^9，最多只有九个不同数字
		if(pd(i)){printf("%d",i);return 0;}//输出结束
}
```

---

## 作者：dph754132771 (赞：1)

/\*
\* P:1467

\* Au:Small\_Ash

\* 一道枚举题,主要关键在于判断是否是循环数,所以我直接在程序里注释了

\* 代码:

\*/
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
long long start;
bool pd(long x){
    if (x==0) return false;//0不是 
    bool v[15];memset(v,false,sizeof v);
    int num=0,a[15];long long xx=x;//备用x 
    while (x) {num++;x/=10;}//计算位数 
    for (int i=num;i>=1;i--){//存每位的数(高精既视感) 
        a[i]=xx%10; 
        xx/=10; 
        if (a[i]==0||v[a[i]]) return false;//如果带0或者有重复数字就退 
        else v[a[i]]=true;//打标记 
    }
    if (num==1) return true;//一位数肯定是循环数 
    if (num==2){
        if (a[1]%2!=0&&a[2]%2!=0) return true;
        else return false;
```
}//二位数的优化,双位奇数就是循环数,否则不是
```cpp
    memset(v,false,sizeof v);//三位以上的顺序搜索 
    int time=0,i=1;//time已搜索个数i当前位置 
    for (;time<num;){
        if (!v[i]) v[i]=true;//还未被访问 
        else return false;//访问过就退 
        time++;
        i=(i+a[i])%num;//到下一位 
        if (i==0) i=num;//重要,记得我们的位数是从1开始的(大神可尝试直接0开始,就不用这句了) 
    }
    if (i!=1) return false;//重要,如果没回原位也要退 
    return true;//重关过后修得正果... 
}
int main(){
    scanf("%lld",&start);start=start+1;//记得要加1,因为求的是大于M的数,我就这么WA了一个点QAQ 
    while (!pd(start)) start++; //直接线性枚举 
    printf("%d\n",start);
    return 0;
}

```

---

## 作者：「QQ红包」 (赞：1)

这道题翻译得不是特别好，读题需要仔细，然后判断什么的都要有。总的来说算是复杂的枚举题

```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
//#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
long long n;int i; 
int a[30],b[30],ii,c[30],be,f;//a存被强拆的n的每一位，ii存被拆的数的长度 
void chai(long long gg)
{
    ii=1;//防止报错? 
    int x=0;
    int aa[233]={0};
    long long g;
    g=gg; 
    while (g>0)
    {
        x++;//记位数 
        b[x]=g%10;
        if (aa[b[x]]==1)//重复了 
        {
            f=0;
            ii=1;//存下位数?防止报错！ 
            return;
        }
        if (b[x]==0)//不能有0 
        {
            f=0;
            ii=1;//存下位数?防止报错！ 
            return;
        }
        aa[b[x]]=1;//标记 
        g=g/10; 
```
}//把g强拆了。
```cpp
    ii=x;//存下位数 
    for (i=1;i<=x;i++)
        a[i]=b[ii-i+1];//正着存到a数组 
    return;
} 
int main() 
{
    freopen("runround.in","r",stdin);
    freopen("runround.out","w",stdout);
    cin>>n;//读入n;
    do
    {
        n++;
        f=1;//标记用，1代表这个数符合条件 
        chai(n);//把n拆了 
        //int yu=n%ii;//求出余数,数其实只要数余数 
        a[0]=a[ii];//如果数到余数是0的话，就是a[n]
        for (i=0;i<30;i++) c[i]=0;//清0 
        be=1;//be是起始位;
        if (f==1)//已经被排除的情况不要继续搜了 
            for (i=1;i<=ii;i++)//有多少位进行多少次枚举，出现 
            {
                be=(be+a[be])%ii;//求第i次将被标记的数 
                if (c[be]==1)//搜过辣，之后肯定会死循环 
                {
                    f=0;//标记这个数不符合条件 
                    break;//退出 
                }
                c[be]=1;//标记; 
            }
        if (f==1)//如果这个数符合条件 
        {
            printf("%d\n",n);
            return 0;
        } 
    }
    while (true);
    return 0;
}

```

---

## 作者：clockwhite (赞：0)

蒟蒻的思路：爆搜。

这道题的**重难点**主要在于如何频繁的**将当前测试的数++，**

很显然，由于题目中出现了21位这样的~~毒瘤~~数据，我觉得
```
while（1）M++，分解数字（），check（）；
```

肯定不行~~TLE~~那么就如同高精度，用**数组**存下来。emmm，++的实现虽然高精度也有，但是感觉太麻烦（不会写），并且每次只加1，就不用高精度那么麻烦，我就手打了一个（见code中bg函数）。
然后就是check（）；

这题有四个坑点（并非难点），

**1.所有数位都要访问到，**

**2.不得出现重复数字，**

**3.不得出现0,**

**4.循环之后要回到起点**

emmm，我写题的时候就只注意到了1.，后面三个是看了数据再看一遍题才看出来的（血的教训）

然后无限从左到右循环（求余）没什么问题，几个小函数写写（其实小函数比较好改，哪里出错改哪里）
就ok了。
ACcode：
```cpp
int a[666],l=20,r=20,s,ok=1;
//r为数字的最右边的下标+1，l为最左边，左闭右开
bool vis[666],sz[10];//访问标记和数字标记
inline void read() {//魔改版快读
	char ch=getchar();
	while(ch>='0'&&ch<='9') {
		a[r++]=ch-'0';
		ch=getchar();
	}
}
inline void bg(int i) {//修改数字
	l=min(l,i);//实时记录最左边
	a[i]++;
	if(a[i]==10) {//不能有零
		a[i]=1;
		bg(i-1);//进位
	}
}
inline void pr() {//输出
	for(int i=l; i<r; i++)printf("%d",a[i]);
}
inline bool check2() {//判断重复数字
	memset(sz,0,sizeof(sz));
	for(int i=l; i<r; i++) {
		if(sz[a[i]])return 0;
		sz[a[i]]=1;
	}
	return 1;
}
inline void check1() {//判断是否是循环数
	int i=l,tot=0;//累加器和当前的下标
	memset(vis,0,sizeof(vis));
	while(!vis[i]) {
		vis[i]=1;
		tot++;
		i=l+(i-l+a[i])%(r-l);//求余代码
	}
	if(tot==r-l&&i==l) {//所有的都访问且回到起点
		ok=0;
		pr();
	}
}
int main() {
	read();
	while(ok) {//ok为是否找到答案
		bg(r-1);//变更个位
		if(check2())check1();
	}
}
```
萌新题解希望通过qwq，拒绝作弊，营造良好洛谷

---

## 作者：loi_hjh (赞：0)

~~听说题解里有许多用while的大佬，难道只有我用for吗~~

#为了怕有人抄袭，我改了个小地方（本地可以过），小心CE~~（狡黠一笑）~~

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<iostream>
#include<algorithm>
using namespace std;
int l,step,a[10001],b[10001],len,n;
bool vis[10001]; 
inline int ll(int x){//根据我队某大佬的话说inline在函数前（递归除外）里可以加速 
    len=0;//这个数的长度 
    while(x>=1){//逆序存储 
        b[++len]=x%10;
        x/=10;
    };
    for(int i=1;i<=len;i++)
    	a[len-i+1]=b[i];//再把逆序正过来（我是强迫症，勿喷） 
    return len;
}
inline bool gg(){
    int t=1;
    memset(vis,false,sizeof(vis));
    for(register int i=1;i<=l;i++){
        if((vis[a[t]])||(!a[t])) return false;//题目说不能有0 
        vis[a[t]]=true;//走过了; 
        t=(t+a[t])%l;//走到下一位上; 
        if(!t) t=l;
    }
    if(t!=1) return false;//要走到第一个才行 
    return true;
}
int main(){
    scanf("%d",&n);
    for(register int i=n+1;i<=2147483647;i++){//最开始写的i=n，然后总是86，怎么改也不对，原来。。。 
    	l=ll(i);
    	if(gg()){
    		printf("%d",i);
    		break;//找到了
		}
	}
    return ~~(0-0);//卖个萌求通过 
}


```

---

## 作者：zhangyuhan (赞：0)

eh...我把这道题做成了搜索！

主要思路：从输入的数+1开始，不断往上循环，判断该数是否为循环数。

这道题主要考验你的耐心，看起来容易，做起来难！

话不多说，奉上AC代码（注释均在代码内）
```cpp
#include<iostream>
using namespace std;
int x;
int cnt;
int old_num[12],num[12];
bool ans[12];
void statistics(int a)//统计该数的数位长度和各个数位
{
    cnt=0;
    while(a!=0)
    {
        cnt++;
        old_num[cnt]=a%10;
        a/=10;
    }
}
bool all()//判断每一位是否都遍历过了
{
    for(int i=1;i<=cnt;i++)
    {
        if(!ans[i])
            return false;
    }
    return true;
}
bool dfs(int pointer)
{
    int far;//指循环到的下一位
    far=(pointer+num[pointer])%cnt;
    if(far==0)
        far=cnt;
    if(far==1&&all())//全部遍历过且下一位是第一位，就是循环数
        return true;
    if(far==1&&!all())//虽然下一位是第一位但是并没有把每一位全部遍历，还不是循环数
        return false;
    if(ans[far]==true)//如果下一位不是第一位但是下一位已经遍历过，不是循环数
        return false;
    ans[far]=true;//指下一位被遍历
    dfs(far);//搜索下一位
}
int main()
{
    cin>>x;
    for(int i=x+1;;i++)
    {
        int flag=0;
        statistics(i);
        int f=cnt;
        for(int j=1;j<=cnt;j++)
        {
            num[j]=old_num[f];
            f--;
        }//将逆序改为正序
        for(int j=1;j<=cnt;j++)
        {
            if(num[j]==0)
            {
                flag=1;
                break;
            }
            for(int k=1;k<j;k++)
            {
                if(num[j]==num[k])//判断其中每一位是否都不重复
                {
                    flag=1;
                    break;
                }
            }
            if(flag)
               break;
        }
        if(flag)
            continue;
        else
        {
            ans[1]=true;
            if(dfs(1))
            {
                cout<<i;
                break;
            }
        }
        for(int j=1;j<=cnt;j++)
        {
            old_num[j]=0;
            num[j]=0;
            ans[j]=0;
        }//注意一定要清零！！！
    }
    return 0;
}

```

---

## 作者：Celebrate (赞：0)

这一题采用纯暴力法，竟然能AC

从m+1开始依次枚举，如果可以就输出，不可以就继续

代码如下：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
bool f[21];
inline bool pd(int k)//判断这个数的数位有没有重叠 
{
	memset(f,false,sizeof(f));//f数组记录每一个数字 
	while(k>0)
	{
		if(f[k%10]==true || k%10==0) return false;//如果重复 
		f[k%10]=true;k/=10;//继续 
	}
	return true;//没有重复的话 
}
int len,a[21],top;
bool v[21];
inline bool find_loop(int k)//判断这个数是否为循环数 
{
	top=1;int t=top;//t表示当前的位置 
	do
	{
		t=t+a[t];if(t>len) t%=len;//找下一个位置 
		if(t==0) t=len;
		if(v[t]==false && t!=top) return false;//如果这个位置重复了，就肯定不是循环数 
		v[t]=false;//标记为走过 
	}while(t!=top);
	for(int i=1;i<=len;i++) if(v[i]==true) return false; 
	return true;//如果遍历了所有的位置，就是循环数 
}
int main()
{
	int m,t;
	scanf("%d",&m);
	while(1)
	{
		m++;//往下依次枚举 
		if(pd(m)==true)//如果没有相同的数字 
		{
			t=m;len=0;
			while(t>0)//拿出每一个数 
			{
				len++;a[len]=t%10;t/=10;
				v[len]=true;
			}
			for(int i=1;i<=len/2;i++){int t=a[i];a[i]=a[len+1-i];a[len+1-i]=t;}//因为前面是从后往前的，所以要把方向变一变 
			if(find_loop(1)==true)//如果是循环数 
			{
				printf("%d\n",m);break;//输出并且推出while循环 
			}
		}
	}
	return 0;
}
```

---

## 作者：Jianyang (赞：0)

竟然没有pascal题解？来一发

这题是一道细节很多的纯模拟题，本蒟蒻的方法是从n+1开始搜索直到找到循环数，判断时直接边模拟边mod（数的位数）遍若回到原位置——1，则是循环数

可以将数字转成字符串以便计算长度、每一位数字

话不多说，上代码：

```cpp
var n:qword;//题目说明了，要开qword
function jj:boolean;//判断是否为循环数的子程序
var i,j:longint;//循环变量（要开longint）
    k,t,l,x:qword;//k是当前位置，t是当前共走几步，L是字符串长度，x用来字符串转一位数字（本蒟蒻习惯只要不是循环变量就开qword，反正空间充足，免的少开）
    w:array[0..99]of qword;//计数器
    s:string;//以字符串的形式存当前找到的数字
begin
  k:=1;//把当前位置设为1
  t:=0;//当前还没走，所以是0步
  str(n,s);//将数字转成字符串以便计算长度和每一位数字
  l:=length(s);//用L存下数字长度
  fillchar(w,sizeof(w),0);//初始化
  for i:=1 to l do//这里是统计有无重复数字或数字0，如果有，就不可能是循环数（自己思考一下），直接返回false
  begin
    val(s[i],x);//将这一位字符转成数字x
    if(w[x]>0)or(x=0)then//如果这个数字出现过或者是0
    exit(false);//返回false并直接跳出子程序
    inc(w[x]);//计数
  end;
  fillchar(w,sizeof(w),0);//继续初始化计数器
  while t<l do//模拟l遍循环判断（程序核心！）
  begin
    val(s[k],x);//将这一位字符转成数字x
    if w[x]>0 then//继续判断是否有重复数字（想一想为什么）
    exit(false);
    inc(w[x]);//记录次数
    inc(t);//更新t
    k:=(k+x)mod l;//更新k
    if k=0 then//可能出现k为0的情况
    k:=l;//要把k赋成L
  end;
  if k<>1 then//如果k没回到1（不是循环数）
  exit(false);//返回false并跳出
  exit(true);//返回true
end;
begin
  read(n);//读入
  while true do//此处不用设定跳出条件，可以在找到答案后直接输出并结束程序
  begin
    inc(n);//寻找循环数（注意，要先加后检验，题目要求找的是比n大的循环数）
    if jj then//如果这个数是循环数
    begin
      write(n);//直接输出
      halt;//结束程序
    end;
  end;
end.
```

---

## 作者：TBB_Nozomi (赞：0)

这题可以不用模仿高精加嘛= =！

这个题目的题干有明确写出来是**不包括0且没有重复数字的整数**，也就是说最多最多是一个九位数

枚举这样的九位数的种类数大概是9!左右，而且你还不会用把所有的数字都枚举玩，dfs暴力搜每一个数多好！

那么判断它是不是一个循环数的方法，就是从第一个数开始循环直到循环出来的结果的数字已经被循环过了为止，还要注意检查它是否大于输入的数

以下代码用一个check函数来表示判定now数组是否为循环数

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int now[20]={0},in_base=0;
bool use[10]={false};
bool check(int dig)    {
    bool che[20]={0};
    int i=0,S=0;
    while(!che[i])    {
        che[i]=true;
        i=(i+now[i])%dig;
        S++;
    }
    return (S==dig)&&(i==0);
}
void dfs(int deep_dig,int dig)    {
    if(dig==deep_dig)    {
        int S=0;
        for(int i=0;i<dig;i++)    S=S*10+now[i];
        if(S<=in_base)    return;
        if(check(dig))    printf("%d",S),exit(0);
        return ;
    }
    for(int i=1;i<=9;i++)    {
        if(use[i])    continue;
        use[i]=true;
        now[dig]=i;
        dfs(deep_dig,dig+1);
        use[i]=false;
    }
    return ;
}
int main()    {
    scanf("%d",&in_base);
    for(int i=1;i<=10;i++)    dfs(i,0);
    return 0;
}
```

---

