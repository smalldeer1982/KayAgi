# PIN Codes

## 题目描述

### 题意简述

众所周知，PIN 码是由 $4$ 个数码组成的字符串。

现在有 $n$ 个 PIN 码。你可以**多次**修改某些 PIN 码中的一位。问至少需要修改多少次，才能使得所有的 $n$ 个 PIN 码**互不相同**。

## 样例 #1

### 输入

```
3
2
1234
0600
2
1337
1337
4
3139
3139
3139
3139
```

### 输出

```
0
1234
0600
1
1337
1237
3
3139
3138
3939
6139
```

# 题解

## 作者：rrrrr (赞：5)

#### 思路
因为n<10  

所以pin值末尾为0-9时一定不会重复   

只要把重复的末尾值再在0-9枚举一遍就可以了

#### 实现 
用 map q 记录是否出现过  

map p 是否访问过   

若访问过加入原值a[i]   

没有访问过加入变化过的a[i]  

用 pit储存答案

```
#include<bits/stdc++.h>
using namespace std;
int pit[11111],t,n,a[1111111];
int main()
{
	cin>>t;
	for(int ii=1;ii<=t;ii++)
	{
		map<int,int>q;
		map<int,int>p;
		int ans=0,tl=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			q[a[i]]=1,p[a[i]]=1;//记录
		}
		for(int i=1;i<=n;i++)
		{
			if(q[a[i]]==1)
			{
				if(p[a[i]]==1)//没有访问过
				{
					pit[++tl]=a[i];
					p[a[i]]-=1;
				continue;
				}
				ans++;//访问过答案++
				for(int j=0;j<=9;j++)
				{
					if(q[a[i]/10*10+j]==0)
					{ 
						q[a[i]/10*10+j]++,pit[++tl]=a[i]/10*10+j;//变化，输出
						break;
					}
				} 
			} 
			else
			q[a[i]]++,pit[++tl]=a[i];
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)
		{
			cout<<pit[i]/1000%10<<pit[i]/100%10<<pit[i]/10%10<<pit[i]%10<<"\n";
		}
	}
}
```

---

## 作者：Kizuna_AI (赞：2)

我的博客：https://likecoding.tech

首先，**随机数牛逼**！

由于使用了随机数，不能保证100%的AC，可能会有出现WA的情况

思路，由于$n \leq 10$重复的概率十分小，因此可以直接通过随机数的方法来解决。

我们逐个将重复的数字放到set中，如果set里已经存在，那么我们使用随机数更改任意一位，并修改成0-9的任意一个。通过这种方式就可以解决了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,id[15];
string p[15];
set<string> s;
bool cmp(const int &x,const int &y) {
	if(p[x]<p[y]) return true;
	else return false;
}
int main() {
	srand(time(0));
	scanf("%d",&T);
	while(T--) {
		s.clear();
		int cnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			cin>>p[i],id[i]=i;
		sort(id+1,id+1+n,cmp);
		for(int i=1;i<=n;i++){
			if(s.find(p[i])!=s.end()) {
				cnt++;
				int rrd=rand()%4;
				for(int k=0;k<10;k++) {
					int rd=rand()%10;
					p[i][rrd]=rd+'0';
					if(s.find(p[i])==s.end()) break;
				}
			}
			s.insert(p[i]);
		}
		cout<<cnt<<'\n';
		for(int i=1;i<=n;i++)
			cout<<p[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：2)

# 思路

数据范围$2\leq n\leq 10$，且每个数只有$4$位，所以可以暴力。

对于每个数，暴力枚举个位到千位，把一位上的数替换掉，看看行不行。

变量名：

`vis[i]`表示`i`这个数有没有被用掉。

`vector<int>v[10005]`,`v[i]`存储`i`这个数在原数组中哪些位置出现（方便修改）。

把一位上的数替换掉的代码：
```cpp
inline int change(int x,int p,int num){
	//把x的第p位替换为num
	int p10=pow(10,p);//p10=10的p次方
	int th=(x/p10)%10;//第p位的数
	x-=th*p10;
	x+=num*p10;
	return x;
}
```
关于输出部分：题目要求输出$4$位，不足的补$0$，那就这样做：
```cpp
cout<<setw(4)<<setfill('0')<<a[i]<<'\n';
```
其中`setw(4)`表示$4$位宽度，`setfill('0')`表示不足的补$0$。

其他注释在代码中。

# 代码
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,a[111];
int vis[10005];
vector<int>v[10005];
inline int change(int x,int p,int num){
	int p10=pow(10,p);
	int th=(x/p10)%10;
	x-=th*p10;
	x+=num*p10;
	return x;
}
void work()
{
	int res=0;
	memset(vis,0,sizeof vis);
	For(i,0,9999)v[i].clear();
	n=read();
	For(i,1,n)a[i]=read(),vis[a[i]]=1,v[a[i]].push_back(i);
	For(i,0,9999){
		if(v[i].size()<2)continue;//如果个数<2，无冲突，不用改。
		For(j,1,v[i].size()-1){
			res++;//改一次
			For(p,0,3)
			{
				bool flag=1;
				For(num,0,9)
				{
					int x=change(i,p,num);
					if(!vis[x]){//没有过这个数
						vis[x]=1;//标记掉
						a[v[i][j]]=x;//原数组修改
						flag=0;//表示找到了，已修改
						break;
					}
				}
				if(!flag)break;//找到了，直接退出。
			}
		}
	}
	cout<<res<<endl;
	For(i,1,n)cout<<setw(4)<<setfill('0')<<a[i]<<'\n';
}
signed main()
{
	int t=read();
	while(t--)work();
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
简单的思维题。
## 分析。
注意到 $n$ 的最大范围只有 $10$ 所以必定能保证存在至少一种方案可以使得它们互不相同。那么如果输出的数串之间至少存在一位互不相同，则修改 $0$ 次，反之，我们需要改变其中的某一位。我们发现，我们可以通过对于相同的字符串，改变求第一个字符或者最后一个字符来使得它们不一样。

我们有这样一种思路：采用字符串的思想，在输入的过程中标记每一个字符串的最后一个字符，然后向前寻找是否有和当前字符串相同的字符串，如果有，那么用从 $0$ 到 $9$ 的任意一个没有在末尾出现的数替换掉原来的最后一位即可。因为数据范围的限制，所以必定都能互不相同。最后把用过的这个用来替换的数标记一下，继续输入即可。注意到，因为我们在每个输入的字符串中都进行了操作，所以可以保证在当前字符串之前的每一个字符串两两不同，所以只看最后一位就行了。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int t,n;
char s[10][5];
int sum,used[10];
int main(){
    cin>>t;
    while(t--){
        memset(used,0,sizeof(used));
        cin>>n;
        sum=0;
        for(int i=0;i<n;i++){
            cin>>s[i];
            used[s[i][3]-'0']=1;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){//枚举前面的字符串。 
                if(strcmp(s[i],s[j])==0){//若有相同的。 
                    for(int k=0;k<10;k++){
                        if(used[k]==0){//如果存在一个数没有被使用过。 
                            s[i][3]=k+'0';
                            sum++;//更改一次。 
                            used[k]=1;//标记已经使用。 
                            break;
                        }
                    }
                }
            }
        }
        cout<<sum<<"\n";
        for(int i=0;i<n;i++){
        	cout<<s[i]<<"\n";
		}
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Goodrage (赞：0)

看了各位大佬的题解，有的用散列表，```vector```，随机数和双 ```map```，蒟蒻表示 **这道题不用这么复杂吧** ……一个 ```map``` 足够了。

#### 思路分析

我们先将所有的 $a_i$ 全部读入，用一个 ```map``` 标记每种密码的出现次数，然后因为 $n \leqslant 10$，直接枚举改变个位即可。而且如果一个密码出现多次，我们保持它最后出现的一次不变，改变前面的重复密码。

用数组直接保存 $a_i$，也省去了从 $0$ 一直到 $9999$ 的循环枚举。

数字的转化输出都差不多，不多讲述。

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mrx;
int a[25];
int ans;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		mrx.clear();//多测，map一定要清空
		ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);//把数字直接存下
			mrx[a[i]]++;//标记每个密码出现几次
		}
		for(int i=1;i<=n;i++)
		{
			if(mrx[a[i]]==1)//这个数字是它种类的最后一个了，没有人和它重复了
				continue;
			else
			{
				ans++;//需要改变
				for(int j=0;j<=9;j++)//枚举个位并改变
				{
					int tmp=a[i]/10;
					tmp=tmp*10;
					tmp+=j;
			//		printf("%d ",tmp);
					if(mrx[tmp]==0)//查无此数
					{
						mrx[a[i]]--;//a[i]被改掉一个了，所以少了
						a[i]=tmp;
						mrx[a[i]]++;//但是新的数增加了
						break;
					}
				}
			}
		}
		printf("%d\n",ans);//一共改变几个数
		for(int i=1;i<=n;i++)
		{
			printf("%d",a[i]/1000);//逐位输出
			printf("%d",(a[i]/100)%10);
			printf("%d",(a[i]/10)%10);
			printf("%d\n",a[i]%10);
		}
	}
	return 0;
}
```


---

## 作者：xkcdjerry (赞：0)

这道题数据范围很小，那就~~dp~~暴力吧。  
很简单，由于至多有10个，所以肯定在任意一位上每一个PIN码都可以分配一个不同的，就不用考虑要修改两列，所以，对于每一个一样的PIN（可以使用一个散列表`bucket`来维护），考虑每一列中改成哪一个数字就行了。  
为了修改变化，需要使用一个`traceback`数组，对于每一个数字，维护一个长度为10的数组：位为1表示这个数字在此位上，为0则表示不在，比如，若`traceback[1234]`为`{0,0,1,1,0}`，则表示2,3号PIN码为1234  。

所以基本就是这样：
对于每一个重复的数（`while(bucket[i]>1)`）， 

在4个不同的位，每个10个数字(`for(k=0;k<4;k++)` `for(j=0;j<10;j++)`），  
判断是否可以改变（`if(!vis[k][j])`{1}），  
然后通过`traceback`表寻找修改的位置(`for(r=0;r<10;r++)` `if(traceback[i][r])`），  
当寻找到的时候，对答案加一（`ans++`），将`vis[k][j]`置1表示用过同时将`p[r][k]`置为`j`，  
再将`traceback[i][r]`清零，`bucket[i]--`（表示已经改变了{2}）  
然后这里应该跳到`while(bucket[i]>1)`的最后面重新检查  

代码如下：


 ```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZERO(p) memset(p,0,sizeof p)
char p[20][10];
char bucket[10010];
char traceback[10010][10];
char vis[4][10];
int pos[10];
void init()
{
    ZERO(pos);
    ZERO(p);
    ZERO(bucket);
    ZERO(vis);
    ZERO(traceback);
}
int hash(char s[])
{
    return s[0]*1000+s[1]*100+s[2]*10+s[3];
}
void read(char s[])
{
    scanf("%s",s);
    s[0]-='0';
    s[1]-='0';
    s[2]-='0';
    s[3]-='0';
}
void once()
{
    int n,i,j,k,r,ans=0;
    init();
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        read(p[i]);
        bucket[hash(p[i])]++;
        traceback[hash(p[i])][i]=1;
        for(j=0;j<4;j++)
        {
            vis[j][p[i][j]]=1;
        }
    }
    for(i=0;i<10010;i++) // i -> PIN number
    {
        while(bucket[i]>1)
        {
            for(k=0;k<4;k++) // k -> column to change
            {
                for(j=0;j<10;j++) // j ->  number to change to
                {
                    if(!vis[k][j])
                    {
                        for(r=0;r<10;r++) // r -> line to change
                        {
                            if(traceback[i][r])
                            {
                                ans++;
                                vis[k][j]=1;
                                traceback[i][r]=0;
                                p[r][k]=j;
                                bucket[i]--;
                                goto stop;
                            }
                        }
                    }
                }
            }
            stop:;
        }
    }
    printf("%d\n",ans);
    for(i=0;i<n;i++)
    {
        for(j=0;j<4;j++) putchar(p[i][j]+'0');
        putchar('\n');
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--) once();
    return 0;
}

```

注1：`vis[i][j]`表示在第`i`列中，数字`j`是否出现过。  
注2：由于其中一位已经改变为了不与任何一个冲突的数字，即保证了修改后的数组不会再次冲突，就不用把它存在bucket或者traceback数组里了 ~~（我才不会告诉你是我犯懒不想重算了呢）~~

---

