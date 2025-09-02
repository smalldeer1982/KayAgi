# Parity Alternated Deletions

## 题目描述

$Polycarp$有一个有$n$个数的数组，他会轮流从中删去数，比如：奇数-偶数-奇数-偶数-奇数-偶数-奇数-偶数···$\ \ \ $或：偶数-奇数-偶数-奇数-偶数-奇数-偶数-奇数···直到无法删除。

## 样例 #1

### 输入

```
5
1 5 7 8 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
6
5 1 2 4 6 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
1000000 1000000
```

### 输出

```
1000000
```

# 题解

## 作者：la_un_ty (赞：2)

这一道题是暴力模拟题。

$$\begin{matrix} \large m\acute{o}& n\check{i}\\\Huge\text{模}&\Huge\text{拟}\end{matrix}$$

先在读入时将奇数和偶数分别压入两个队列。题目中提到，一奇一偶的删除，为使结果最小，所以肯定是先删大的数。

经过分析发现，当$\text{两条队列长度差}≤1$时便可将其全部删除完，此时输出$0$。

剩下的数就按照题目上所说的一个一个轮流减去即可。

代码如下：

```
#include<bits/stdc++.h>
#define int long long//保险起见，先开long long
using namespace std;
int n,ans=0,tmp=0;
vector<int> odd,even;//奇数偶数队列
int it1=0,it2=0;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>tmp;ans+=tmp;//此时记录一下和
		if(tmp&1/*这里是用位运算判断奇偶*/) odd.push_back(tmp);
		else even.push_back(tmp);//分别压入。
	}
	sort(odd.begin(),odd.end());//因为要删除，所以要排序。
	sort(even.begin(),even.end());//从后往前从大到小删除
	bool tag=odd.size()>even.size();//tag表示先删奇数还是偶数
	it1=odd.size()-1;//我本想用迭代器来着
	it2=even.size()-1;//记录一下队列顶
	while(1){
		if(tag){//如果该删奇数
			if(it1<0){
				break;
			}
			ans-=odd[it1];//把他从ans中减去
			it1--;//指针前移
		}
		if(!tag){
			if(it2<0){
				break;
			}
			ans-=even[it2];//同上
			it2--;
		}
		tag=!tag;//交换删除状态
     /*也可写成tag^=tag*/
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：犇犇犇犇 (赞：2)

### 竟然没有题解？自己来一发。

### 大家不要被题目难度标签吓到，这道题其实没那么难。

题目大概意思就是有一个$n$个数的数列，删掉一个奇数再删掉一个偶数，求最后剩下的数和最小是多少。

所以就可以有贪新的思路了，**从最大的开始删**，先删奇数和先删偶数分开讨论，最后取$min$就是最优解了。

由于我们每次都要删掉**最大**的数，所以可以用**优先队列把奇数偶数分别保存进去**，要取数直接$pop$就好了

所以接下来做法就很简单了

```
#include <bits/stdc++.h>
using namespace std;
int a[2005],n,s1,s2,t;
priority_queue<int> q1,q2; //分别保存奇数数列和偶数数列
int main()
{
    int i;
    cin>>n;
    for(i=1;i<=n;++i)
        cin>>a[i];
    for(i=1;i<=n;i++)
    {
    	s1+=a[i]; //统计先删奇数的和
    	if(a[i]%2==1) q1.push(a[i]); //如果是奇数就放入奇数数列
        else q2.push(a[i]); //同上
	}
    while(!q1.empty())
    {
        t=q1.top(); //取出当前奇数的最大数
        s1-=t; 
		q1.pop(); //把这个数删掉
        if(q2.empty()) 
			break; //如果偶数被删光了，直接退出
        t=q2.top(); //取出偶数最大
        s1-=t;
        q2.pop(); //把偶数最大的删掉
    }
    while(!q1.empty()) q1.pop();
    while(!q2.empty()) q2.pop(); //把奇偶队列清空
    for(i=1;i<=n;i++)
    {
    	s2+=a[i];
    	if(a[i]%2==1) q1.push(a[i]);
        else q2.push(a[i]);
	}
    while(!q2.empty())
    {
        t=q2.top();
        s2-=t;
        q2.pop();
        if(q1.empty()) 
			break;
        t=q1.top();
        s2-=t;
        q1.pop();
    } //同上，统计先删偶数的情况
    cout<<min(s1,s2)<<endl; //两种情况取最小值得到答案
    return 0;
}

``` 




---

## 作者：Priori_Incantatem (赞：1)

这题其实就是纯模拟，~~肯定没有蓝题的难度,顶多就是个黄题~~

本人用到了STL的vector，若不了解vector可以看下这两个博客  
[vector用法整理](https://www.cnblogs.com/Nonono-nw/p/3462183.html)  
[sort-vector](https://www.cnblogs.com/helloWaston/p/4584324.html)

如题有两种删除方法：  
奇数-偶数-奇数-偶数-奇数-偶数  
偶数-奇数-偶数-奇数-偶数-奇数  
所以要考虑两种方法中剩余数的和最小

要想剩余的和最小，每次就要尽量删除大的数，所以把这段序列按升序（从小到大）排序，然后每次找最大的

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
int n,ans1,ans2;//要考虑两种结果
vector <int> a,b;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int t;
        scanf("%d",&t);
        a.push_back(t);
        b.push_back(t);
    }
    sort(a.begin(),a.end());//升序排列
    sort(b.begin(),b.end());//升序排列
    for(int i=1;i<=n;++i)//先删奇数再删偶数
    {
        int mod=i%2;//先删奇数再删偶数
        int j=a.size()-1;
        while(a[j]%2!=mod&&j>=0)j--;//寻找最大的符合要求的数
        if(j<0)break;//判断没有符合要求的数的情况
        a.erase(a.begin()+j,a.begin()+j+1);//将数删除
    }
    for(int i=0;i<a.size();++i)
    ans1+=a[i];//求剩下的数的和
    for(int i=0;i<n;++i)//先删偶数再删奇数
    {
        int mod=i%2;//先删偶数再删奇数
        int j=b.size()-1;
        while(b[j]%2!=mod&&j>=0)--j;//与上面同理
        if(j<0)break;
        b.erase(b.begin()+j,b.begin()+j+1);
    }
    for(int i=0;i<b.size();++i)
    ans2+=b[i];
    printf("%d\n",min(ans1,ans2));//输出最小值
    return 0;
}
```

---

## 作者：Lucifer_Bartholomew (赞：1)

# 模拟
模拟'先取奇数'和'先取偶数'的两种情况,最后输出两种情况得到的sum值中最小的就行了。
```cpp
#include <queue>
#include <cstdio>
#include <algorithm>
#define rr register int
using namespace std;
inline int read()
{
    char ch=getchar();
    if(!(~ch))return 0;
    int f=1;
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    int x=0;
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int a[2000];
priority_queue<int> q1,q2,Q1,Q2;//大根堆,记数列中最大的数
int main()
{
    int n=read(),sum1=0,sum2=0;//分别记录两种情况各自的sum值
    for(rr i=0;i<n;++i)
    {
        a[i]=read();
        sum1+=a[i];
        sum2+=a[i];
        if(a[i]&1)//奇数单独记一列
        {
            q1.push(a[i]);
            Q1.push(a[i]);
        }
        else//偶数单独记一列
        {
            q2.push(a[i]);
            Q2.push(a[i]);
        }
    }
    while(!q1.empty())//第一种情况
    {
        int now=q1.top();
        q1.pop();
        sum1-=now;
        if(q2.empty())break;
        now=q2.top();
        q2.pop();
        sum1-=now;
    }
    while(!Q2.empty())//第二种情况
    {
        int now=Q2.top();
        Q2.pop();
        sum2-=now;
        if(Q1.empty())break;
        now=Q1.top();
        Q1.pop();
        sum2-=now;
    }
    printf("%d\n",min(sum1,sum2));//输出sum最小值
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：kfhkx (赞：1)

题目大意：

给出n个数并进行以下两个操作
1. 随便选择一个数，将其删去
2. 如果1.删去的是奇数，则随便删去一个偶数；如果1.删去的是偶数，则随便删去一个奇数；如果数列中没有符合的数，则结束以上操作；反之继续操作2.

现在问剩下的数总和最小是多少？

思路：

将n个数分奇数和偶数分别存在两个数组里并统计个数，然后分别进行从大到小排序，最后再从大到小删去就行了~。

另外，一遇到没有符合的数就直接退出~

附pascal代码

### CF1144B.pas


------------

```pascal
var
        n,i,ans,tot1,tot2,x,h:longint;
        a:array[0..100000,0..2] of longint;
function max(x,y:longint):longint;
begin
        if x>y then exit(x) else exit(y);
end;
procedure kp(x,y,z:longint);//快排
var
        l,r,m:longint;
begin
        l:=x;
        r:=y;
        m:=a[(l+r)>>1,z];
        repeat
                while a[l,z]>m do inc(l);
                while a[r,z]<m do dec(r);
                if l<=r then begin
                        a[0,z]:=a[l,z];
                        a[l,z]:=a[r,z];
                        a[r,z]:=a[0,z];
                        inc(l);
                        dec(r);
                end;
        until l>r;
        if x<r then kp(x,r,z);
        if l<y then kp(l,y,z);
end;
begin
        readln(n);
        for i:=1 to n do begin
                read(x);
                if x mod 2=1 then begin//判断奇偶
                        inc(tot1);//统计奇数个数
                        a[tot1,1]:=x;
                end else begin
                        inc(tot2);//统计偶数个数
                        a[tot2,2]:=x;
                end;
        end;
        kp(1,n,1);//分别两次从大到小快排
        kp(1,n,2);
        h:=max(tot1,tot2);//取奇偶个数最大
        for i:=1 to h do begin
                if (a[i,1]>a[i,2]) and (tot1>0) then begin//去数过程
                        a[i,1]:=0;
                        dec(tot1);
                        if tot2=0 then break else begin//判断此时个数是否为0
                                a[i,2]:=0;
                                dec(tot2);
                        end;
                end else if (a[i,1]<a[i,2]) and (tot2>0) then begin
                        a[i,2]:=0;
                        dec(tot2);
                        if tot1=0 then break else begin//判断此时个数是否为0
                                a[i,1]:=0;
                                dec(tot1);
                        end;
                end else if a[i,1]=a[i,2] then break;//若发现此时两数相同（即为两个个数都没有了）
        end;
        for i:=1 to h do ans:=ans+a[i,1]+a[i,2];//统计答案
        writeln(ans);
end.
```

---

## 作者：Nemonade (赞：0)

提供一种新思路。

把奇数偶数分成两组。因为是选一个奇数一个偶数，所以说最后必定会有一组会删完，删去的奇数和偶数的个数差 $\le 1$。

再想一个贪心，如果能取数尽量取最大的。所以我们统计偶数和奇数的个数 $m_0$ 和 $m_1$，然后从大到小先把偶数奇数都删掉 $\min(m_0,m_1)$ 个，统计剩下数的和，再考虑一下多取一个的情况就好了。

注意如果 $m_0$ 和 $m_1$ 的差 $\le 1$ 要特判全部取完。代码很短。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define pfor(i,x,y) for(register int i=x;i<=y;++i)
#define mfor(i,x,y) for(register int i=x;i>=y;--i)
inline int read(){
	int x=0;bool flag=false;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') flag=true;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return flag?~x+1:x;
}
inline void write(int x){
	if(x<0){putchar('-');x=(~x+1);}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=2e3+5;
int n,a[N],m[2],res;
vector<int> v[2];//用vector记录偶数奇数 
signed main(){
	n=read();
	pfor(i,1,n){
		a[i]=read();
		++m[a[i]&1];//统计偶数奇数个数 
		v[a[i]&1].push_back(a[i]); 
	}
	sort(v[0].begin(),v[0].end());//升序排序 
	sort(v[1].begin(),v[1].end());
	if(abs(m[0]-m[1])<=1){puts("0");return 0;}//上面说的特判 
	if(m[0]>m[1]){//考虑多取一个的情况，统计的时候就要少加一个 
		pfor(i,0,v[0].size()-m[1]-2) res+=v[0][i];
		cout<<res;
	}
	else{
		pfor(i,0,v[1].size()-m[0]-2) res+=v[1][i];
		cout<<res;
	}
	return 0;
}
```

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

Polycarp 有一个包含 $n$ 个整数的数组 $a$；

他想在这个数组上玩一个游戏，游戏包含了若干次操作。第一次操作他会选择任意一个元素，并删除它；接下来每次操作中他选取并删除的元素需要满足一个限制：本次操作与上次操作中数字的奇偶性不同。当无法删除元素时，游戏停止。

Polycarp 的目标是最小化游戏停止时数组中还未被删除的数字之和。如果所有元素都被删掉，数字之和为 $0$。

## 思路

第一次选的数的奇偶性取决了答案，所以选的第一个数有两种选择：
1. 选奇数

2. 选偶数

那么该怎么选择呢？

很简单，只用看数组里偶数多还是奇数多。

如果奇数多的话，那么偶数全部都会选完，剩下的只能是奇数；那么会剩下多少奇数呢？

我们已经知道，奇数偶数是轮流选的，所以可以看成是选一次奇数，一次偶数为一组，但最后还可以多选一次，所以还要减去 $1$。

所以可以将数组分为两个数组，一个是长度为 $x$ 的奇数数组 $a$，一个数长度为 $y$ 的偶数数组 $b$；

那么答案就为：

$\sum_{i = 1} ^ {n - y - 1} a_i$

当然，偶数多就为:

$\sum_{i = 1} ^ {n - x - 1} b_i$

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2005;

int n, a[N], lsum, rsum, l[N], r[N];

signed main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] % 2 == 0){
            l[++lsum] = a[i]; // 分为两个小数组
        } else {
            r[++rsum] = a[i];
        }
    }
    sort(l + 1, l + 1 + lsum); // 贪心思想，先把大的拿了，剩下的之和就为最小和
    sort(r + 1, r + 1 + rsum); 
    int ans = 0;
    if(lsum > rsum){
        for(int i = 1; i <= lsum - rsum - 1; i++){ // 直接套公式
            ans += l[i];
        }
    } else {
        for(int i = 1; i <= rsum - lsum - 1; i++){
            ans += r[i];
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：fanfansann (赞：0)

# $B.\ Parity\ Alternated\ Deletions$
$Description$

Polycarp有一个有n个数的数组，他会轮流从中删去数，比如：奇数-偶数-奇数-偶数-奇数-偶数-奇数-偶数··· 或：偶数-奇数-偶数-奇数-偶数-奇数-偶数-奇数···直到无法删除。

$Solution$

~~太水了太水了~~ 

直接模拟就好。
先算一下奇数和偶数的个数，如果个数相同或者差值就输出0（可以取完）
然后排个序，根据题意模拟取最小的即可。


$Code$
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>

#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
#define lowbit(p) p&(-p)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;

const int N = 2e3+7;


int n;
int odd[N],even[N];
int main()
{
    scanf("%d",&n);
    int tot1 = 0;
    int tot2 = 0;
    over(i,1,n){
        int a;
        scanf("%d",&a);
        if(a&1)
            odd[++tot1] = a;
        else even[++tot2] = a;
    }
    if(abs(tot1 - tot2)<=1){
        puts("0");
        return 0;
    }
    sort(odd+1,odd+1+tot1);
    sort(even+1,even+1+tot2);
    int ans = 0;
    if(tot1>tot2){
        for(int i = 1;i <(tot1-tot2);++i)
            ans += odd[i];
        printf("%d\n",ans);
    }
    else {
         for(int i = 1;i <(tot2-tot1);++i)
            ans += even[i];
        printf("%d\n",ans);
    }
    return 0;
}

```


---

## 作者：修罗海神王 (赞：0)


### 有一些OI的题目，你需要将自己融入其中悟得道理。
#### 但这道题目不同，你要做一个局外人的角度来看它。
让我们开始吧！

1、不开long long见祖宗。

2、输入之后，可以将整个数组进行一遍排序，方便以后的查找。

3、然后循环一遍，找出这个数是奇数还是偶数，用数组存储，并进行计数。

4、判断。如果两数之差取绝对值<=1，那么就说明这组数是可以被匹配完的，所以我们可以直接输出0，别忘了换行，然后再return 0掉，防止节外生枝。

5、再次排序。以防万一，将得到的两组数字重新排序。

6、再次判断，因为不知道剩下的数是奇数还是偶数，所以需要一个if，加上一个else。

7、在if中如果奇数小于偶数，那么剩余的数的数量就是偶-奇-1，s清0，然后计数。

8、否则，剩余的数的数量就是奇-偶-1，s清0，然后计数。

9、最后输出s，换行。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a1,a0,a[30000],A1[30000],A0[30000],x,s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2==1) a1++,A1[a1]=a[i];
		  else a0++,A0[a0]=a[i];
	}
	if(abs(a1-a0)<=1) {cout<<"0\n";return 0;}
	sort(A1+1,A1+a1+1);sort(A0+1,A0+a0+1);
	if(a1<a0)
	{
		x=a0-a1-1;s=0;
		for(int i=1;i<=x;i++) s+=A0[i];
		cout<<s<<"\n";return 0;
	}
	else
	{
		x=a1-a0-1;s=0;
		for(int i=1;i<=x;i++) s+=A1[i];
		cout<<s<<"\n";return 0;
	}
	return 0;
}
```
# ~~AC抱回家~~


---

## 作者：米奇奇米 (赞：0)

## 这是一题很简单的蓝题，我看题解里各种各样样的方法，在这里我给大家讲一种更加简单易懂的方法。

### 首先我们判断输出为$0$很简单，只要求出数列里的奇数个数以及偶数个数，然后判断两种情况，只要满足其一即可：
#### $sum1$表示偶数的数量，$sum2$表示奇数的数量，只要满足：$sum1+1==sum2 or sum2+1==sum1$就输出$0$
### 对于其他的情况,要求最小值:如果奇数的个数多于偶数的个数，那么只要将奇数排个序，然后从小到大累加$sum2-sum1-1$项奇数即可。否则如果奇数个数多于偶数个数，只要从小打到累加$sum1-sum2-1$项偶数即可求解了。

### 我造一组数据来解释一下：$3,2,1,2,3,1,3,2$,$O(n)$扫一遍得到$sum1=3,sum2=5$,那么我们可以用$3$个偶数消掉$4$个较大的奇数：$3,2,3,2,3,2,1$(就是按照题意里的奇数、偶数、奇数、...的规律消掉），只剩下了$1$,所以求解为$1$啊！

### 下面我就贴代码了：
```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1e12
using namespace std;
const int N=20005;
int a[N],n,m,ans,minn=inf,sum1,sum2,ord[N],jisu[N];
bool cmp(int a,int b){
	return a>b;
}//结构体，从大到小排序
signed main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]%2==0) ord[++sum1]=a[i];
		if(a[i]%2==1) jisu[++sum2]=a[i];
	}
	if(sum1==sum2+1 || sum1==sum2-1) return puts("0"),0;
	sort(ord+1,ord+sum1+1,cmp); sort(jisu+1,jisu+sum2+1,cmp);
	//for(register int i=1;i<=sum1;i++) cout<<ord[i]<<endl;
	if(sum1>sum2){
		for(register int i=sum2+2;i<=sum1;i++) ans+=ord[i];
		return printf("%lld\n",ans),0;
	}
	else{
		for(register int i=sum1+2;i<=sum2;i++) ans+=jisu[i];
		return printf("%lld\n",ans),0;
	}
	return 0;
}
```
### 前面解释的很多了，代码就不多加解释


---

## 作者：αnonymous (赞：0)

其实这道题很简单，首先把数组排好序，暴力枚举去掉符合条件的最大的数。

*重点：假如奇数个数大于总数一半，则先从奇数开始消除数可以消除更多的数。

如果偶数个数大于总数一半，则先从偶数开始消除
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n,a[2001],ji;
bool f[2001];//统计去掉的数
int main(){
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]%2)
			ji++;//记录奇数个数
	}
	sort(a+1,a+n+1);
	if(ji>n/2)//如果奇数个数大于总数一半，则从奇数开始消除
		k=1;//k为1时消除奇数
	else
		k=0;//k为0时消除偶数
	for(i=n;i>=1;i--){//枚举消除n次
		for(j=n;j>=1;j--)//从最大数开始判断
			if(!f[j])
				if(k==1&&a[j]%2==1){
					k=0;//转换为偶数
					f[j]=1;//记录已被消除
					break;
				}
				else if(k==0&&a[j]%2==0){
					k=1;
					f[j]=1;
					break;
				}
	}
	long long total=0;
	for(i=1;i<=n;i++)
		if(!f[i])//如果未被消除，则计入总数
			total+=a[i];
	cout<<total<<endl;
	return 0;
}
```


---

## 作者：_Give_up_ (赞：0)

第一次见到这道题以为很水，调了半天才过。

## 题目思路

删除的规律是一个奇数，一个偶数或者一个偶数，一个奇数，要想所有的数都删完，奇数和偶数的差不能超过 $1$，这一点应该很容易想到，所以如果奇数和偶数的差不超过 $1$，就不用做下面操作。

然后该考虑的就是奇数和偶数的差超过了 $1$，就需要两个数组 $a$ 和 $b$，$a$ 数组储存奇数，$b$ 数组储存偶数。

如果奇数的个数大于偶数，就把储存奇数的数组排序，因为偶数的个数比奇数小，所以偶数肯定都能删没，接下来就是求和了，因为偶数都能删没，只需要遍历装奇数的数组。偶数删完了，题目要求规则是删一个偶数，再删一个奇数，所以奇数也能删同样个偶数加一。从 $1$ 开始遍历，遍历到奇数的个数减偶数的个数再减一，用计数器加起来，就是得到的答案。

如果偶数的个数大于奇数，就把上面奇数变成偶数，偶数变成奇数，反过来就行了。



## 代码

```cpp
#include<bits/stdc++.h>
#define N 2022

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int a[N],b[N];

int main()
{
	int n=read(),ans1=0,ans2=0,x;
	for (int i=1;i<=n;i++)
	{
		if ((x=read())&1) a[++ans1] = x;
		else b[++ans2] = x;
	}
	int ans = 0;
	if (abs(ans1-ans2)>1)
	{
		if (ans1<ans2)
		{
			sort(b+1,b+ans2+1);
			for (int i=1;i<ans2-ans1;i++)
				ans += b[i];
		}
		else
		{
			sort(a+1,a+ans1+1);
			for (int i=1;i<ans1-ans2;i++)
				ans += a[i];
		}
	} 
	cout << ans << endl;
	return 0; 
}
```


---

