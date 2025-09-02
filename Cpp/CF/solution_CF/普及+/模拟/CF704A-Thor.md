# Thor

## 题目描述

（可能无关紧要的地方有点漏洞，但不会影响题意）

雷神常常要去地球，所以洛基给**她**一款智能手机作为礼物。手机上安装了n款应用，每款应用都会跳出很多消息，在每一单位时间，会发生以下3种事件之一：

- 1) 第x个应用跳出了一条消息

- 2) 雷神读了第x个应用跳出的所有消息

- 3) 雷神读了所有应用跳出的前x条消息

雷神很不喜欢手机上有一堆“99+”，所以**她**希望知道，每一分钟后有多少条新消息未读。

## 说明/提示

对于100%的数据，满足$1<=n,q<=300000$，且保证每个事件合法。

## 样例 #1

### 输入

```
3 4
1 3
1 1
1 2
2 3
```

### 输出

```
1
2
3
2
```

## 样例 #2

### 输入

```
4 6
1 2
1 4
1 2
3 3
1 3
1 3
```

### 输出

```
1
2
3
0
1
2
```

# 题解

## 作者：Sea_Level (赞：4)

这道题只要按题意模拟即可。直接上代码：

```cpp
#include<iostream>
#include<queue>//使用c++中STL库的自带队列
using namespace std;
queue<int> que[300010];//二维队列，它用来存每个app的信息（具体结构：que[哪个app].push(哪条信息)）。
queue<pair<int,int> > t;//这个用来存所有信息序号的及是哪个app的
//注：这个t和上面那个que不是一个意思，que的意思是存下每个app的信息，以便操作2使用，t的意思是存下所有信息，以便操作3使用。
int v[300010];//判断这条信息是否读过
int n,q,cnt=1,ans=0;//n和q就是题目中说的，cnt表示信息的序列号，ans存未读的信息数。
int main(){
	cin>>n>>q;
	for(int i=1;i<=q;i++){//循环q次
		int f,num;//f表示他是什么操作（1还是2还是3），num就是题目中的x。
		cin>>f>>num;
		if(f==1){//第x个应用跳出了一条消息
			ans++;//未读信息+1
			que[num].push(cnt);//存储他是第几条信息。
			t.push(make_pair(cnt,num));//存储他是第几条信息和是哪个app的。
			cnt++;//序号+1
		}
		if(f==2){//雷神读了第x个应用跳出的所有消息
			while(que[num].size()){//当第x个应用的信息还没有读完时
				v[que[num].front()]=1;//这条信息设为已读过
				que[num].pop();//把读过的信息删除，que只存未读过的信息
				ans--;//未读过的信息-1
			}
		}
		if(f==3){//雷神读了所有应用跳出的前x条消息
			while(t.size()&&t.front().first<=num){//当前x条信息还没读完
				if(!v[t.front().first]){//如果这条信息没读过，因为有可能在之前的2操作中就已经把这条信息读完了
					v[t.front().first]=1;//设为已读过
					que[t.front().second].pop();//把已读过的信息删除
					ans--;//未读过信息-1
				}
				t.pop();//把已读过的信息删除
			}
		}
		cout<<ans<<endl;//输出未读过的信息
	}
	return 0;//功德圆满，华丽结束
}
```


---

## 作者：shiroi (赞：2)

依据题意直接进行模拟即可。

我们对于每一个应用都维护一个队列，之后只需记录消息的编号，并且记录每一个消息是属于哪一个应用即可。

对于每个输入都进行模拟，这样每条消息只会进队出队一次。


```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

const int MAXN = 300005;
queue<int> a[MAXN];
int num[MAXN];
int n,m,q,ans,lst;

int main(int argc, char const *argv[])
{
	n=read(); q=read();
	for(int i=1; i<=q; i++)
	{
		int opt=read(),t=read();
		if(opt==1) ans++,num[++m]=t,a[t].push(m);
		else if(opt==2)
			while(!a[t].empty())
				a[t].pop(),ans--;
		else
		{
			while(lst<t)
			{
				lst++;
				if(!a[num[lst]].empty())
					if(a[num[lst]].front()<=lst)
						a[num[lst]].pop(),ans--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：yuangq (赞：2)

这题不是很难想，但需要用队列和哈希加速

最暴力的算法
~~~
#include<bits/stdc++.h>
using namespace std;
int n,Q;
int s,w;
struct xiaoxi{
	int ying;
	bool yi;
};
xiaoxi dui[5005];
int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=0;i<Q;i++)
	{
		int a,t;
		scanf("%d%d",&a,&t);
		if(a==1)
		{
			//****************
			w++;
			s++;
			dui[w].yi=0;
			dui[w].ying=t;
			//****************
		}
		if(a==2)
		{
			//****************
			for(int j=1;j<=w;j++)
			{
				if(dui[j].ying==t)
				{
					if(dui[j].yi==0)
					{
						dui[j].yi=1;
						s--;
					}
				}
			}
			//****************
		}
		if(a==3)
		{
			//****************
			for(int j=w;j>w-t;j--)
			{
				
				if(dui[j].yi==0)
				{
					dui[j].yi=1;
					s--;
				}
		
			}
			//****************
		}
		printf("%d\n",s);
	} 
	return 0;
}
~~~

第7个点Tle代码
~~~
#include<bits/stdc++.h>
using namespace std;
struct mes{
	int num;
	bool cmp;
};
queue<mes> a[300005];
int ans[300005];
int N,Q;
int w,s;
int main()
{
	cin>>N>>Q;
	for(int i=0;i<Q;i++)
	{
		int q,x;
		cin>>q>>x;
		if(q==1)
		{
			w++;
			s++;
			mes news;
			news.num=w;
			news.cmp=0;
			a[x].push(news);
			ans[w]=x;
		}
		if(q==2)
		{
			while(a[x].empty()==0)
			{
				mes t=a[x].front();
				if(t.cmp==0)
				{
					t.cmp=1;
					s--;
				}
				a[x].pop();
			}
		}
		if(q==3)
		{
			for(int j=1;j<=x;j++)
			{
				if(a[ans[j]].empty()==1 || j!=a[ans[j]].front().num)
				{
					continue;
				}
				mes t=a[ans[j]].front();
				if(t.cmp==0)
				{
					t.cmp=1;
					s--;
				}
				a[ans[j]].pop();
			}
		}
		cout<<s<<endl;
	}
	return 0;
}
~~~

Ac代码
~~~
#include<bits/stdc++.h>
using namespace std;
struct mes{//代表一条信息 
	int num;//第几条信息 
	bool cmp;//是否被读 
};
queue<mes> a[300005];//n个应用的消息 
int ans[300005];//哈希表 
int N,Q;
int w,s;
int maxs;
int main()
{
	cin>>N>>Q;
	for(int i=0;i<Q;i++)
	{
		int q,x;
		cin>>q>>x;
		if(q==1)
		{
			w++;
			s++;
			mes news;
			news.num=w;
			news.cmp=0;
			a[x].push(news);//将消息弹入队列 
			ans[w]=x;
		}
		if(q==2)
		{
			while(a[x].empty()==0)//将相应队列清空 
			{
				mes t=a[x].front();
				if(t.cmp==0)
				{
					t.cmp=1;
					s--;
				}
				a[x].pop();
			}
		}
		if(q==3)
		{
			if(x<=maxs)//将前x条清空 
			{
			}
			else
			{
				for(int j=maxs;j<=x;j++)
				{
					if(a[ans[j]].empty()==1 || j!=a[ans[j]].front().num)
					{
						continue;
					}
					mes t=a[ans[j]].front();
					if(t.cmp==0)
					{
						t.cmp=1;
						s--;
					}
					a[ans[j]].pop();
				}
				maxs=max(maxs,x);
			}
		}
		cout<<s<<endl;//输出 
	}
	return 0;
}
~~~

---

