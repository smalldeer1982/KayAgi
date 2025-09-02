# Game of Credit Cards

## 题目描述

After the fourth season Sherlock and Moriary have realized the whole foolishness of the battle between them and decided to continue their competitions in peaceful game of Credit Cards.

Rules of this game are simple: each player bring his favourite $ n $ -digit credit card. Then both players name the digits written on their cards one by one. If two digits are not equal, then the player, whose digit is smaller gets a flick (knock in the forehead usually made with a forefinger) from the other player. For example, if $ n=3 $ , Sherlock's card is $ 123 $ and Moriarty's card has number $ 321 $ , first Sherlock names $ 1 $ and Moriarty names $ 3 $ so Sherlock gets a flick. Then they both digit $ 2 $ so no one gets a flick. Finally, Sherlock names $ 3 $ , while Moriarty names $ 1 $ and gets a flick.

Of course, Sherlock will play honestly naming digits one by one in the order they are given, while Moriary, as a true villain, plans to cheat. He is going to name his digits in some other order (however, he is not going to change the overall number of occurences of each digit). For example, in case above Moriarty could name $ 1 $ , $ 2 $ , $ 3 $ and get no flicks at all, or he can name $ 2 $ , $ 3 $ and $ 1 $ to give Sherlock two flicks.

Your goal is to find out the minimum possible number of flicks Moriarty will get (no one likes flicks) and the maximum possible number of flicks Sherlock can get from Moriarty. Note, that these two goals are different and the optimal result may be obtained by using different strategies.

## 说明/提示

First sample is elaborated in the problem statement. In the second sample, there is no way Moriarty can avoid getting two flicks.

## 样例 #1

### 输入

```
3
123
321
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
88
00
```

### 输出

```
2
0
```

# 题解

## 作者：封禁用户 (赞：7)

嗯，贪心。

由于只有第一个人可以移动卡牌，那我们以他为中心开展讨论好了。

首先排一下序。

用a[i] 代表第一个人的当前的数字的大小。

b[j] 代表第二个人的当前的数字的大小。

对于每一次替换，我们都可以是看做将第二个人的坐标往后推了一位，也就是说j++;

对于第一个问题，

若第二个人当前项小于第一个人，那么我们替换一次，并ans++;

否则i++,j++并继续枚举下去。

第二个问题就是反一下，思路相同。

有关代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QAQ 23333
char a[QAQ];
char b[QAQ];
int main(){
	int n;
	scanf("%d",&n);
	scanf("%s%s",a,b);
	sort(a,a+n);
	sort(b,b+n);
	int ans=0;
	int i,j;
	i=j=0;
	while(i<n&&j<n){
		if(b[j]>=a[i]){
			i++;
			j++;
		}
		else{
			j++;
			ans++;
		}
	}
	i=j=0;
	int ans2=0;
	while(i<n&&j<n){
		if(b[j]>a[i]){
			i++;
			j++;
			ans2++。;
		} 
		else j++;
	}
	printf("%d\n%d",ans,ans2);
}
```

---

## 作者：QwQcOrZ (赞：6)

题目要求是只有M能调换顺序，所以我们很容易想到用桶存储M的

第一问：遍历S，先判断是否可以让M不受惩罚，可以就选最小的（贪心），否则选还剩下的中的最小的（贪心）

第二问：遍历S，先判断是否可以让S受惩罚，可以就选最小的（贪心），否则选还剩下的中的最小的（贪心）

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,temp['9'+1],s['9'+1];
string a,b;

int main()
{
    scanf("%d\n",&n);
    cin>>a>>b;
    a=" "+a;
    b=" "+b;
    int ans=n;
    for (int i=1;i<=n;i++) s[b[i]]++,temp[b[i]]++;
    for (int i=1;i<=n;i++)
    {
    	bool t=0;
    	for (char j=a[i];j<='9';j++) if (s[j]) //从a[i]开始
    	{
    		t=1;
    		s[j]--;
    		ans--;
    		break;
        }
        if (t) continue;
    	for (char j='0';j<='9';j++) if (s[j])
    	{
    		s[j]--;
    		break;
        }
    }
    printf("%d\n",ans);
    ans=0;
    for (int i=1;i<=n;i++)
    {
    	bool t=0;
    	for (char j=a[i]+1;j<='9';j++) if (temp[j]) //从a[i]+1开始，这是两个for最主要的区别
    	{
    		t=1;
    		temp[j]--;
    		ans++;
    		break;
        }
        if (t) continue;
    	for (char j='0';j<='9';j++) if (temp[j])
    	{
    		temp[j]--;
    		break;
        }
    }
    printf("%d\n",ans);

    return 0;
}
```

---

## 作者：珅肐 (赞：5)

由题目可以知道

求$M$的最多不输次数和最多能赢次数

其实两者间就差了一个等号

#### 考虑贪心：

都从最小的比较，如果$M$可以赢，那就出这张牌，因为这已经是$M$最小的牌了，不亏

如果$M$不能赢，就留到最后出给$S$最大的牌（听过田忌赛马的故事吗嘿嘿）

使这张牌利益最大化

做两遍，一遍可以等号一遍不行

说一下$S$为什么也可以排序：因为$M$可以任意调换出牌顺序，那么$S$的出牌顺序就对他无所谓了，所以可以排序

### 完整代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<algorithm>
using namespace std;
inline int read(){//快读，可快了，虽然这道题没用
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
char a[1007],b[1007];
int main(){
	int n=read(),j=0,ans=0;//j表示S的当前牌是第几张
	scanf("%s",a),scanf("%s",b);
	sort(a,a+n),sort(b,b+n);//从小到大排序
	for(int i=0;i<n;++i)if(b[i]>=a[j])j++,ans++;//j++表示S出了当前牌，否则S出了他最大的牌
	printf("%d\n",n-ans);j=ans=0;//别忘了清空
	for(int i=0;i<n;++i)if(b[i]>a[j])j++,ans++;//再做一遍
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：wzm2007 (赞：3)

	排个序,用a[i]代表第一个人的当前的数字的大小,b[j]代表第二个人的当前的数字的大小,对于每一次替换,我们都可以是看做将第二个人的坐标往后推了一位,也就是说j++
	1. 若第二个人当时小于第一个人,那么我们替换一次,并ans++,否则i++,j++并继续枚举下去。
	2.与上个相反

------------

    #include<bits/stdc++.h>
    using namespace std;
    char a[1010],b[1010];
    int main()
    {
        int n,i=0,j=0,ans1=0,ans2=0;
        cin>>n>>a>>b;
        sort(a,a+n),sort(b,b+n);
        while(i<n&&j<n)
            if(b[j]>=a[i])i++,j++;
            else j++,ans1++;
        i=j=0;
        while(i<n&&j<n)
            if(b[j]>a[i])i++,j++,ans2++;
            else j++;
        cout<<ans1<<endl<<ans2;
    }

---

## 作者：Lacrymabri (赞：3)

说一种其他方法(其实是我太蒟蒻了没有想到直接贪心就可以做出来....)

设夏洛克的卡片为数组a
莫里亚蒂的卡片为数组b

如果要求莫里亚蒂不被弹额头,则需要满足b[i]>=a[i]
对于任意b[i]大于a[i]就连一条边,n-最大匹配就是答案.这样就是一个裸的二分图匹配了,直接用匈牙利算法就可以做出来.

同理,如果要求莫里亚蒂弹夏洛克的额头,就要求b[i]>a[i],最大匹配就是答案.同理,在跑一次匈牙利算法就可以了.

下面就是我的代码.直接用匈牙利算法会超时,我就用栈在跑匈牙利算法的时候记下来了所有被访问的点.这样子就不需要在每次执行匈牙利算法前将所有vis数组都清零了,快了不少.
```cpp
#include<iostream>
#include<stack>
#define MAX 1005
using namespace std;
short a[MAX];
short b[MAX];
bool map[MAX][MAX];
int match[MAX];
bool vis[MAX];
int n;
stack<int> t;
bool findmatch(int u){
    for(int i=0;i<n;i++){
        if(map[u][i]&&vis[i]){
            vis[i]=false;
            t.push(i);
            if(match[i]==-1||findmatch(match[i])){
                match[i]=u;
                return true;
            }
        }
    }
    return false;
}
int main(){
    char ch;
    cin>>n;
    
    ch=getchar();
    for(int i=0;i<n;i++){
        while(ch<'0'||ch>'9') ch=getchar();
        a[i]=ch-'0';
        ch=getchar();
    }
    ch=getchar();
    for(int i=0;i<n;i++){
        while(ch<'0'||ch>'9') ch=getchar();
        b[i]=ch-'0';
        ch=getchar();
    }
    int sum=0;
    for(int i=0;i<n;i++){
        match[i]=-1;
        for(int j=0;j<n;j++)
            map[i][j]=false;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i]>=a[j]) map[i][j]=true;
            //	else break;
        }
    }
    for(int j=0;j<n;j++) vis[j]=true;
    
    for(int i=0;i<n;i++){
        while(t.size()){
        	vis[t.top()]=true;
        	t.pop();
		}
        sum+=findmatch(i);
    }
    cout<<n-sum<<endl;
    
    sum=0;
    for(int i=0;i<n;i++){
        match[i]=-1;
        for(int j=0;j<n;j++)
            map[i][j]=false;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i]>a[j]) map[i][j]=true;
            //	else break;
        }
    }
    
    for(int j=0;j<n;j++) vis[j]=true;
    
    for(int i=0;i<n;i++){
        while(t.size()){
		   vis[t.top()]=true;
		   t.pop();	
	}
        sum+=findmatch(i);
    }
    
    cout<<sum<<endl;
    
    return 0;
} 
```

---

## 作者：Yhlo_Yzj (赞：0)

## CF777B 题解
**本题题意**：有两个人 $S$ 和 $M$ ，他们每人有一段长度为N的数字，两个人在每一轮游戏中都可以按顺序拿出一个数字，谁的数字小谁就接受一次惩罚。若相等两者
都没有惩罚。

**注**：$M$ 可以重新排自己的顺序。

**问题**: $M$ 的最少被惩罚次数 和 $S$ 的最多被惩罚次数 是多少。

**本题思路————排序和模拟**

1. 本题只说了可以给 $M$ 排序，但你只要个 $M$ 排了序，那 $S$ 也得要排序，故，两个都要排

1. 模拟田忌赛马的过程，打不过的，往后推，找下一个比他大的

1. 重复两遍过程即可输出

接下来————上代码

### $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e3+5;//内存容量
char n[MAXN],m[MAXN];
int l;
int main(){
	cin>>l;
	for(int k=1;k<=l;k++){
		cin>>n[k];//输出字符
	}
	for(int k=1;k<=l;k++){
		cin>>m[k];
	}
	sort(n+1,n+1+l);//排序
	sort(m+1,m+1+l);
	int i=1,j=1,sum=0;
	while(i<=l && j<=l){//田忌赛马
		if(n[i]>m[j]){//惩罚一次，下一张牌继续与他比较
			j++,sum++;
		}else{
			i++,j++;//若无，都换成下一张
		}
	}
	cout<<sum<<endl;
	i=1,j=1,sum=0;
	while(i<=l && j<=l){//重复
		if(n[i]<m[j]){
			sum++,i++,j++;
		}else{
			j++;
		}
	}
	cout<<sum;
	return 0;
}

```


---

## 作者：wcarry (赞：0)

### 题目大意：
#### $Sherlockh$和$Moriary$两人各有$n$张牌。两人每次各取一张，点数小的被惩罚。
#### 问：
* $Moriarty$ 受到惩罚可能的最少次数
* $Sherlock$ 可能受到惩罚最多的次数

#### 思路：
#### 要想惩罚少，合理分配不可少。$Moriarty$要是用$9$去与$Sherlock$的$1$比，岂不是亏大了，所以尽量使两个大小差不多但我就比你大一点点。（就和田忌赛马一样）

#### 解法:
#### 先把两人的牌从大到小排序，然后逐一比较就能实现以上思路了。

#### 具体点，
#### 第一种，两个人比较，想要$Moriarty$受到惩罚最少，从大到小逐一比较，若$M$牌大于等于$S$牌则$M$与$S$都往后比。若$M$牌小于 $S$牌 ，$ans$（惩罚数）$+1$且当前$S$的下一张与当前$M$比。

#### 第二种，使$Sherlock$惩罚最多，跟第一种相似：从大到小逐一比较，若$M$牌大于$S$牌则$M$与$S$都往后比。若$M$牌 小于等于$S$牌 ，$ans$（惩罚数）$+1$且当前$S$的下一张与当前$M$比。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
template <typename T>
inline void read(T &x){
    x=0;re char ch=getchar();re bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
int const N=1e2+5;
int s[N],m[N];
inline bool cmp(int x,int y){
	return x>y;
}
int main(){
	int n;read(n);
	string s1,m1;
	getline(cin,s1);
	getline(cin,m1);
	for(re int i=0;i<n;++i){
		s[i+1]=s1[i]-'0';
		m[i+1]=m1[i]-'0';
	}
    
	//situation 1
	sort(s+1,s+n+1,cmp);
	sort(m+1,m+n+1,cmp);
	int now=1;
	int ans1=0,ans2=0;
	for(re int i=1;i<=n;++i){
		if(m[now]>=s[i]) now++;
		else ans1++;
	}
	write(ans1);putchar('\n');
    
	//situation 2
	now=1;
	for(re int i=1;i<=n;++i){
		if(m[now]>s[i]) now++,ans2++;
	}
	write(ans2);putchar('\n');
	return 0;
}
```

---

## 作者：Skies (赞：0)

这道题是贪心简单题

首先，如果我现在有一张牌，再本轮可以获胜的情况下

### 一定会和对方<=本张牌 的最大的那张来比赛

只是两个小问有些不一样

第一问取等，第二问不取等

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int N=1010;
int a[N],b[N];
bool v[N];
int rd()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'&&c<'0')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x*f;
}
int main()
{
	//freopen
	n=rd();
	for(int i=1;i<=n;i++)
	{
		a[i]=getchar()-'0';
	}
	getchar();
	for(int i=1;i<=n;i++)
	{
		b[i]=getchar()-'0';
	}
	sort(a+1,a+n+1);sort(b+1,b+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int k=upper_bound(a+1,a+n+1,b[i])-a;
//		cout<<k;
		bool fl=0;
		for(int j=k-1;j>0;j--)
		{
			if(!v[j])
			{
				v[j]=1;
				fl=1;
				break;
			}
		}
		if(!fl)
		{
			ans++;
		}
	}
	printf("%d\n",ans);
	ans=0;
	memset(v,0,sizeof(v));
	for(int i=1;i<=n;i++)
	{
		int k=lower_bound(a+1,a+n+1,b[i])-a;
//		cout<<k;
		for(int j=k-1;j>0;j--)
		{
			if(!v[j])
			{
				v[j]=1;
				ans++;
				break;
			}
		}
		
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：魁父 (赞：0)

老样子，话少点吧
```pascal
var
 i,n,j,s1,s2:longint;
 a:array[1..3,0..1000] of char;//为什么要这样呢,后面揭晓
 t:char;
procedure qsort(h,l,r:longint);//快排
var i,j:longint; m:char;
begin
  i:=l;
  j:=r;
  m:=a[h,(l+r) div 2];
  repeat
  while a[h,i]<m do inc(i);
  while a[h,j]>m do dec(j);
  if i<=j then
    begin
    t:=a[h,i];
    a[h,i]:=a[h,j];
    a[h,j]:=t;
    inc(i);
    dec(j);
    end;
  until i>j;
  if l<j then qsort(h,l,j);
  if i<r then qsort(h,i,r);
end;
begin
  readln(n);
  for i:=1 to n do read(a[1,i]);readln;
  for i:=1 to n do read(a[2,i]);//输入
  qsort(1,1,n);
  qsort(2,1,n);//嘿嘿，知道了吧
    i:=1;j:=1;
    while (i<=n)and(j<=n) do
      begin
        if a[2,j]>=a[1,i] then
          begin
            inc(i);
            inc(j);
            if a[1,i]<>a[2,j] then 
          end
        else
          begin
            inc(j);
            inc(s1);
          end;
       end;//计算M的最少被惩罚次数
    i:=1;j:=1;
    while (i<=n)and(j<=n) do
      begin
        if a[2,j]>a[1,i] then
          begin
            inc(i);
            inc(j);
            inc(s2);
          end
        else inc(j);
      end;//计算S的最多被惩罚次数
  writeln(s1);writeln(s2);//输出
end.
```
就这样结束啦

---

