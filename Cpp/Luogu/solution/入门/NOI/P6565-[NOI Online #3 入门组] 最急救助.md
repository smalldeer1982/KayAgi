# [NOI Online #3 入门组] 最急救助

## 题目描述

救助中心每天都要收到很多求救信号。收到求救信号后，救助中心会分析求救信号，找出最紧急的求救者给予救助。

求救信号是一个由小写英文字母组成的字符串，字符串中连续三个字符依次组成`sos`的情况越多（即包含子串`sos`的数目越多），代表着求救者情况越紧急。

现在请你帮助救助中心找出最紧急的求救者。注意字符串中包含的`sos`可以有重叠，例如`sosos`算作包含 $2$ 个`sos`。

## 说明/提示

#### 数据规模与约定

- 对于 $10\%$ 的数据，$n=1$。
- 对于所有数据，$1 \leq n\le 100$，求救者名字长度不超过 $20$，求救信号长度不超过 $200$。



## 样例 #1

### 输入

```
2
adam
ineedhelpsosineedhelpsos
mark
ineedmorehelpsoshelpmesossoshelpme```

### 输出

```
mark
3```

## 样例 #2

### 输入

```
3
susan
sosososososos
jack
sossossossos
allen
soshelpsossossossossos```

### 输出

```
susan allen
6```

# 题解

## 作者：云浅知处 (赞：51)

~~这是 NOI Online这么多场比赛中最良心的一道题，没有之一~~

[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-p6565)

------------

题目大意就是给你一堆字符串，然后让你找出哪个字符串中包含的子串 `sos` 最多。

所以，我们要做的事情有：

1. 在一个字符串中寻找子串 `sos` 的数量；
2. 以子串 `sos` 的数量为第一优先级，输入顺序为第二优先级排序；
3. 输出所有子串 `sos` 最多的字符串。

接下来，让我们一步一步切掉这道题吧QwQ！

------------

前置：存储每个人的信息

这里定义一个结构体即可。

```cpp
struct node{
    string name,help;
    int s,num;
    //name 是求助者的名字
    //help 是求助者的求助信息
    //s 是求助信息中子串 sos 的数量
    //num 是求助者的顺序
}str[105];
```

------------


第一步：在一个字符串中寻找子串 `sos` 的数量

这部分是最简单的，直接从头到尾暴力枚举即可。

代码如下：

```cpp
int find(string qwq){                   //寻找子串 sos 的数量
    int len=qwq.size();                 //提取出这个字符串的长度，STL 大法好！QwQ
    int anss=0;                         //子串 sos 的数量
    for(int i=0;i<len-2;i++){           //从头到尾枚举
        if(qwq[i]=='s'&&qwq[i+1]=='o'&&qwq[i+2]=='s'){  //如果这里有一个 sos
            anss++;                     //子串 sos 的数量+1
        }
    }
    return anss;                        //返回子串 sos 的数量
}
```

------------

第二步：以子串 `sos` 的数量为第一优先级，输入顺序为第二优先级排序；

这里也可以利用 `STL` 中的 `sort` 函数，手写一个 `cmp` 比较函数即可。

首先是比较函数 `cmp` ：

```cpp
bool cmp(node p,node q){                //比较函数 cmp
    if(p.s==q.s){                       //如果两个求助信息中的子串 sos 的数量都相同
        return p.num<q.num;             //按照输入顺序排序
    }
    return p.s>q.s;                     //否则按照求助信息中的子串 sos 的数量排序
}
```

然后，排序部分只有一行：

```cpp
sort(str+1,str+n+1,cmp);            //STL 大法好！QWQ
```

------------

第三步：输出

为了确保输出每一个子串 `sos` 最多的字符串，我们可以定义变量 `tmp` 来表示子串 `sos` 最多有多少个，然后一个一个输出。

一旦出现子串 `sos` 少于 `tmp` 的情况，立刻退出循环，停止输出。

最后，输出 `tmp` 。（因为题目中还说让输出最紧急求救者的求救信号中包含有多少个 `sos` 子串）

代码如下:

```cpp
int tmp=str[1].s;                   //排序之后，最前面的那个自然就是子串 sos 最多的啦QwQ，直接记录即可。
for(int i=1;i<=n;i++){
    if(str[i].s!=tmp){              //如果子串 sos 的数量少于 tmp
        break;                      //立刻退出循环停止输出
    }
    cout<<str[i].name<<" ";
}
cout<<endl<<tmp;                    //别忘了换行哦
```

------------

最后，完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
    string name,help;
    int s,num;
    //name 是求助者的名字
    //help 是求助者的求助信息
    //s 是求助信息中子串 sos 的数量
    //num 是求助者的顺序
}str[105];
int find(string qwq){                   //寻找子串 sos 的数量
    int len=qwq.size();                 //提取出这个字符串的长度，STL 大法好！QwQ
    int anss=0;                         //子串 sos 的数量
    for(int i=0;i<len-2;i++){           //从头到尾枚举
        if(qwq[i]=='s'&&qwq[i+1]=='o'&&qwq[i+2]=='s'){  //如果这里有一个 sos
            anss++;                     //子串 sos 的数量+1
        }
    }
    return anss;                        //返回子串 sos 的数量
}
bool cmp(node p,node q){                //比较函数 cmp
    if(p.s==q.s){                       //如果两个求助信息中的子串 sos 的数量都相同
        return p.num<q.num;             //按照输入顺序排序
    }
    return p.s>q.s;                     //否则按照求助信息中的子串 sos 的数量排序
}
int main(){
    //freopen("save.in","r",stdin);
    //freopen("save.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);                        //黑科技cin,cout加速
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i].name>>str[i].help;
        str[i].s=find(str[i].help);     
        str[i].num=i;
    }
    sort(str+1,str+n+1,cmp);            //STL 大法好！QWQ
    int tmp=str[1].s;                   //排序之后，最前面的那个自然就是子串 sos 最多的啦QwQ，直接记录即可。
    for(int i=1;i<=n;i++){
        if(str[i].s!=tmp){              //如果子串 sos 的数量少于 tmp
            break;                      //立刻退出循环停止输出
        }
        cout<<str[i].name<<" ";
    }
    cout<<endl<<tmp;                    //别忘了换行哦
    return 0;
}
```

____


最后，祝大家：

```cpp
struct node{
    int RP;
}NOI_Online_3rd;
NOI_Online_3rd.RP++;
```


---

## 作者：MyAngelBronya (赞：16)

首先读题，不难理解~~这是一道签到题~~就是在n个字符串里找出sos最多的那个

代码实现思路也很简单

因为有sosos这类的重复的特殊情况存在，所以我们不是从头到尾遍历

而是枚举区间右端点，然后取向左的3个字符拼起来看看是不是sos

这样就可以避免掉重复的问题

贴上代码
```
#include<bits/stdc++.h>
using namespace std;
string name[109],s[109];
int cnt[109];
int main(){
	
	int n,ans=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cnt[i]=0;
		cin>>name[i]>>s[i];
		for(int j=2;j<=s[i].size();j++){
			string q;
			q=s[i][j-2]+s[i][j-1]+s[i][j];
			if(s[i][j-2]=='s'&&s[i][j-1]=='o'&&s[i][j]=='s') cnt[i]++;
		}
		ans=max(ans,cnt[i]);
	}
	for(int i=0;i<n;i++){
		if(cnt[i]==ans) cout<<name[i]<<" ";
	}
	cout<<endl;
	cout<<ans<<endl;
	return 0;
}
```

~~考试时候忘记怎么拼接字符串的我是屑~~


---

## 作者：丧黑福造 (赞：6)

~~这次NOIONLINE的T1是真的良心~~

作为签到题，思路为：**模拟**

~~~~
一个小技巧：我们用string数组来存名字（我没有用结构体）
~~~~
代码：
```cpp
#include <stdio.h>
#include <cstring>
#include <iostream>
int maxn = -0x7fffffff;
int t[105];
using namespace std;
int main() {
	//freopen("save.in","r",stdin);
    //freopen("save.out","w",stdout);
    int n;
    scanf ("%d", &n);
    string sos;
    string name[105];
    for (register int i = 1; i <= n; i ++) {
    	cin >> name[i] >> sos;
    	int len = sos.length();
    	for (register int j = 0; j < len; j ++) {
    		if (sos[j] == 's' && sos[j + 1] == 'o' && sos[j + 2] == 's') {//暴力扫描sos出现的次数
    			t[i] ++;
			}
			maxn = maxn > t[i] ? maxn : t[i];//找sos出现次数最多的一次
		}
    }
    for (register int i = 1; i <= n; i ++)
    	if (t[i] == maxn)
    		cout << name[i] << " ";
    puts("");
	printf ("%d\n", maxn);
    return 0;
}
```

---

## 作者：Veranda (赞：3)

这题**主要思路**就是~~暴力~~用一个指针 $i$ 来扫描整个字符串，如果发现某一个字符为 ```s```，那么判断 $i+1$ 和 $i+2$ 分别是不是 ```o```  和 ```s```，如果是，那么使计数器 $cnt++$，不是就继续扫描下一个即可

**本题的关键点有三个：**
1. 如何处理```sos```两个```s```的重复问题，只需要把当前指针挪到第最后一个```s```上面即可

2. 注意扫描时的越界问题，$i$ 只需要循环到 字符串长度$-2$ 即可

3. 在扫描出一个时将 $i$ 加 $2$ 就行，因为中间那个是 ```o``` 而不是 ```s```，这样可以~~极略微~~的节省时间

**附上代码**：

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;
vector<string> res;
int main() {
	//freopen("save.in","r",stdin);
	//freopen("save.out","w",stdout);
	int n;
	int maxcnt = -1;
	cin >> n;
	while (n--) {
		string name, s;
		int cnt = 0;
		cin >> name;
		cin >> s;
		int len = s.length();
		for (int i = 0; i < len - 2; i++) {
			if (s[i] == 's' && s[i + 1] == 'o' && s[i + 2] == 's') {
				cnt++;
				i++;
			}
		}
		if (cnt > maxcnt) {
			res.clear();
			res.push_back(name);
			maxcnt = cnt;
		}
		else if (cnt == maxcnt) res.push_back(name);
	}
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << endl << maxcnt;
}
```


---

## 作者：江户川·萝卜 (赞：2)

这道题就是对于每一个求救信号计`sos`的个数，然后输出个数最多的人的名字。  
具体看代码。  
考场代码有些丑请见谅。
```cpp
#include<bits/stdc++.h>
#define Fr(i,l,r,x) for(int (i)=(l);(i)<=(r);(i)+=(x))
//#define FILE 
using namespace std;
int n,maxcnt;
struct qjz{//求救者 
	string name;//名字 
	string qjxh;//求救信号
	int len;//求救信号长度 
	int soscnt;//sos计数 
}q[101];
int main(){
#ifdef FILE
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
#endif//文件操作不用管
	cin>>n;
	Fr(i,1,n,1){
		cin>>q[i].name>>q[i].qjxh;//输入姓名和求救信号
		q[i].len=q[i].qjxh.length();
		q[i].soscnt=0;
		Fr(j,0,q[i].len-2,1)
			if(q[i].qjxh[j]=='s'&&q[i].qjxh[j+1]=='o'&&q[i].qjxh[j+2]=='s')//判断qjxh[j]~qjxh[j+2]是否为"sos"
				 q[i].soscnt++;
		if(q[i].soscnt>maxcnt) maxcnt=q[i].soscnt;//如果这个人的sos个数大于之前的最大个数，更新最大个数
	}
	Fr(i,1,n,1)
		if(q[i].soscnt==maxcnt) cout<<q[i].name<<' ';//输出最急求救人的名字
	cout<<endl<<maxcnt;//输出最大"sos"的个数
	return 0;
}
```


---

## 作者：k3v1n070828 (赞：1)

### 简单模拟题

思路：

1.记录每个人的sos数量，记录最大值

2.如果这个人sos数量是最大值，则输出这个人的名字

3.换行后输出最大值

话不多说，上代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
int n;//人数
string name[110],s[110];//人名和信号
int maxn=-100;//最大值
int a[110];//记录每个人的sos数量数组
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
 		cin>>name[i];
		cin>>s[i];
		int len=s[i].size();//记录信号长度
		int cnt=0;
		for(int j=0;j<len-2;j++)
			if(s[i][j]=='s'&&s[i][j+1]=='o'&&s[i][j+2]=='s')
				cnt++;//计数器记录每个人的sos数量
		a[i]=cnt;//赋值到a[i]
		if(cnt>maxn)
			maxn=cnt;//最大值更新
	}
	for(int i=1;i<=n;i++)
		if(a[i]==maxn)
			cout<<name[i]<<" ";//输出最紧急的人名
	printf("\n");//换行
	printf("%d\n",maxn);//最后输出sos最大值
	return 0;//结束程序
} 
```

自己AC吧~

---

## 作者：Lacrymabre (赞：1)

题意简述：给你$n$个字符串，让你数里面分别有几个$sos$。

首先想到KMP，但是这是PJ题，我们用简单的方法：遍历字符串。

找到一个$s$，然后检验后面$2$个是不是$os$就行了。十分简单。

而样例2中的情况，如果更新了最大值就直接替换答案字符串（名字），否则答案字符串+=当前字符串

代码如下：

```
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>

#define ll long long
#define db double
#define MAX 0x7fffffff
#define init inline int
#define INF 0X3fffffff

using namespace std;

inline long long read()
{
    ll f=1,s=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*f;
}


char a[1000];string name,an;
ll p[1000],n,m,ans,res;

int main(){
//	freopen("save.in","r",stdin);
//	freopen("save.out","w",stdout);
	cin>>n;
	while(n--){
		cin>>name;cin>>a;
		ll len=strlen(a);
		for(int i=0;i<len;i++)
			if(a[i]=='s'&&a[i+1]=='o'&&a[i+2]=='s') res++;
			
		if(res>ans) an=name,ans=res;
		else
		if(res==ans) an+=' ',an+=name;
		res=0;
	}
	cout<<an<<endl<<ans;
	fclose(stdin);fclose(stdout);
	return 0;
}
```

本题主要考察for循环！


---

## 作者：novax (赞：0)

做过最简单的NOI Online题目

#### 题意
有 $k$ 个人，每个人有一段呼救的字符串，找出呼救字符串中"sos"最多的人

#### 思路
直接模拟，对于每个人用一个循环，从第3个字符到第 $N$ 个字符，计算第 $i$，$i-1$，$i-2$ 个字符是否分别是"s"，"o"，"s"，如果是，这个人的"sos"数量就加1，最后用一个循环找到所有人的"sos"的最大值，再用一层循环把所有"sos"数量等于这个最大值的人输出就可以了

每个人的数据有名字，求救信号长度，"sos"数量三个，所以可以用结构体来存

#### 代码如下
```
#include <cstdio>
#include <cstring>
int max(int x,int y)
{
	return (x>y)?x:y; 
} 
struct people
{
	char name[30];//求救者名字 
	char ql[220];//求救信号长度
	int qm;//这个人的求救信号长度 
	int lgh;//这个人的求救信号中含有几个'sos' 
};
people a[110];
int N;
int main()
{
	//freopen("save.in","r",stdin);
	//freopen("save.out","w",stdout);
	scanf("%d%d",&N);
	int i,j,t;
	t=0;
	for(i=1;i<=N;i++)//读入数据 
	{
		scanf("%s",a[i].name);
		scanf("%s",a[i].ql);
		a[i].qm=strlen(a[i].ql);
		a[i].lgh=0;
	} 
	for(i=1;i<=N;i++) 
	{
		for(j=2;j<=a[i].qm;j++)
		{
			if(a[i].ql[j]=='s'&&a[i].ql[j-1]=='o'&&a[i].ql[j-2]=='s')
			{
				a[i].lgh++;
			}
		}
	} 
	for(i=1;i<=N;i++)
	{
		t=max(a[i].lgh,t);
	}
	for(i=1;i<=N;i++)
	{
		if(a[i].lgh==t)
		{
			printf("%s ",a[i].name);
		}
	}
	printf("\n%d\n",t);
}
```


---

