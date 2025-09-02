# Vasya and String

## 题目描述

High school student Vasya got a string of length $ n $ as a birthday present. This string consists of letters 'a' and 'b' only. Vasya denotes beauty of the string as the maximum length of a substring (consecutive subsequence) consisting of equal letters.

Vasya can change no more than $ k $ characters of the original string. What is the maximum beauty of the string he can achieve?

## 说明/提示

In the first sample, Vasya can obtain both strings "aaaa" and "bbbb".

In the second sample, the optimal answer is obtained with the string "aaaaabaa" or with the string "aabaaaaa".

## 样例 #1

### 输入

```
4 2
abba
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 1
aabaabaa
```

### 输出

```
5
```

# 题解

## 作者：wuyixiang (赞：11)

## Vasya and String 题解

[题目传送门](https://www.luogu.com.cn/problem/CF676C)

一道双指针水题。

做法：每次移动右端点 $r$，中间取 $\max$，一直移动到不满足条件；然后将左端点 $l$ 往左移，移动到满足条件。此时满足条件了，取最大值即可；然后接着循环，循环至 $r > n$ 结束。

由于字符串 $a$、$b$ 都可以为最长长度，需要循环两次，一次查找 $a$，一次查找 $b$。

### AC code:

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n,l,ans,k,sum,ans2;
int main()
{
	string a;
	cin >> n >> k >> a;
	a = " " + a;
	for(int r = 1;r <= n;r ++)//扫a的最大长度
	{
		if(a[r] == 'a')sum ++;
		while(sum > k && l < r)//不满足条件，左端点往左移
		{
			l ++;
			if(a[l] == 'a')sum --;
		}
		if(r - l > ans)ans = max(ans,r - l);//满足条件，取最大
	}
	l = 0,sum = 0;//记得清空！！！
    for(int r = 1;r <= n;r ++)//扫b的最大长度
	{
		if(a[r] == 'b')sum ++;
		while(sum > k && l < r)
		{
			l ++;
			if(a[l] == 'b')sum --;
		}
		if(r - l > ans2)ans2 = max(ans,r - l);
	}
	cout << max(ans,ans2);//两者取max
   return 0;//完结撒花
}
```


---

## 作者：Miraik (赞：5)

这题最好的方法是尺取，可我太菜了想不到怎么办？

不如暴力二分吧！

用 $a$ 数组存储字符串中每个字符 $\text{a}$ 出现的位置，$b$ 数组存储字符串中每个字符 $\text{b}$ 出现的位置。

对于以第 $i$ 个字符开头的答案字符串，我们用二分法找出第一个在它后面的不同字符的位置，然后就可以得到第 $k+1$ 个在它后面的不同字符的位置 $q$。

那么这个答案串的长度就是 $q-i$。

当然如果在这个字符后面的不同字符个数小于等于 $k$ 个，那么可以直接取到串末，此时这个答案串的长度就是 $n-i+1$。

你以为这就没了？

~~想的太简单了~~

下面这组数据

```
7 2
aabbbbb
```

正确输出是 $7$，但是上述方法输出的是 $5$。

因为这个方法是枚举开头且 **开头不变** 的，所以我们枚举不到改变第一个字符的情况。

因此我们在字符串首加上一个与一个字符相反的字符，计算长度时再将这个字符舍去即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,k,st,cnta,cntb,ans,l,r,mid,a[100005],b[100005];char s[100005];
void work(int i){
	if(s[i]=='a'){
		l=1,r=cntb,st=r+1;//二分，st是第一个在它后面的不同字符的位置的数组下标
		while(l<=r){
			mid=(l+r)/2;
			if(b[mid]>i)r=mid-1,st=min(st,mid);
			else l=mid+1;
		}
		ans=max(ans,((st+k>cntb)?(n+1):(b[st+k]))-((i)?i:1));//i=0时有1个额外字符，要减掉
		//if(i==1)printf("%d\n",st);
		//if(ans==9){printf("%d %d\n",i,st);return 0;}
	}
	else{
		l=1,r=cnta,st=r+1;
		while(l<=r){		
			mid=(l+r)/2;
			if(a[mid]>i)r=mid-1,st=min(st,mid);
			else l=mid+1;
		}
		ans=max(ans,((st+k>cnta)?(n+1):(a[st+k]))-((i)?i:1));
		//if(ans==9){printf("%d %d\n",i,st);return 0;}
	}
}
int main(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	    if(s[i]=='a')a[++cnta]=i;
	    else b[++cntb]=i;
	//printf("%d %d\n",cnta,cntb);
	s[0]=(s[1]=='a')?'b':'a';//补第0个字符（额外字符）
	for(int i=0;i<=n;i++)work(i);
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：C20212724杨京朝 (赞：3)

    #include <cstdio>
    char c[100005];
    int main() {
        int n,k;
        scanf("%d %d",&n,&k);
        for(int i = 0; i < n; i ++) scanf("%c",&c[i]);//输入
        int l = 0,r = 0,ans = 0,sa = 0,sb = 0;//定义两个指针，从左到右扫描
        while(r < n) {//只要r<=n-1(字符串长度）,就继续扫描.
            if(c[r] == 'a') sa ++;
            else sb ++;//扫描时统计a,b的数量
            if(sa <= k || sb <= k) {
                ans ++;
                r ++;
            }//只要sa 或 sb 小于k,就说明可以将该号位进行变化,继续扫描
            else {
                if(c[l] == 'a') sa --;
                else sb --;//判断现在扫描处的开端为a还是b,对应的a,b数量-1。
                l ++;
                r ++;
            }//否则将指针往右移
        }
        printf("%d",ans);//输出答案
        return 0;
    }


---

## 作者：在想Peach (赞：2)

题解好像暂时没有这种做法，发一下

前缀和

对于 $a$ 来说，记录每个位置 $b$ 的前缀和，以及每个前缀和第一次出现的位置，对于每个位置的答案就是 **当前位置** $i$- $($当前位置 $b$ 前缀和 $- k$的前缀和的 **第一次出现位置** $)$ ，因为此时这个位置是最远的符合条件的位置，反之一样，统计所有位置答案即为解。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
using namespace std;
const int maxn=100005;
int T,n,sum0[maxn],sum1[maxn],a[maxn];
int e0[maxn],e1[maxn],k;
bool p0[maxn],p1[maxn];
char s[maxn];
int read(){
	char z=getchar();int x=0,y=1;
	while(z<'0'||z>'9'){if(z=='-')y=-1;z=getchar();}
	while(z<='9'&&z>='0'){x=x*10+z-'0';z=getchar();}
	return x*y;
}
void init(){
	n=read();k=read();
	memset(e0,0x3f,sizeof(e0));memset(e1,0x3f,sizeof(e1));
	cin>>s+1;
	sum0[0]=sum1[0]=0;
	for(int i=1;i<=n;i++){
		sum0[i]=sum0[i-1];sum1[i]=sum1[i-1];
		if(s[i]=='a')a[i]=0,sum0[i]++;
		else a[i]=1,sum1[i]++;
	}
}
void solve(){
	e0[0]=e1[0]=0;p0[0]=1;p1[0]=1;
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,i-e0[max(sum0[i]-k,(int)0)]);if(!p0[sum0[i]]){e0[sum0[i]]=i;p0[sum0[i]]=1;}
		ans=max(ans,i-e1[max(sum1[i]-k,(int)0)]);if(!p1[sum1[i]]){e1[sum1[i]]=i;p1[sum1[i]]=1;}
	}
	cout<<ans<<endl;
}
signed main(){
	init();
	solve();
	return 0;
}
```





---

## 作者：xiongyuhan (赞：1)

话说这道题为什么评蓝啊，就是一双指针水题。

# 具体思路

用两个指针 $l$ 和 $r$ 分别指向区间首和区间尾的上一个，然后不断往前尺取，一直将 $r$ 移动到不满足条件，然后再动 $l$ 移动到满足条件后取个 $\max$ 就行了。

注意：题目中没有说区间一定是 $a$ 或 $b$，所以需要尺取两次分别是改 $a$ 和改 $b$。

**接下来是代码时间！！！**

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, k, ans;
string s;

int main(){
    cin >> n >> k >> s;
    s = " " + s;
    int r = 0, l = 0, sum = 0;
    while(r < n){//把a改成b
        r++;
        if(s[r] == 'a') sum++;//新加的字符为a
        while(sum > k && l < r){
            l++;
            if(s[l] == 'a') sum--;//删去的字符为a
        }
        ans = max(ans, r - l);//求max
    }
    l = r = 0;
    sum = 0;
    while(r < n){//把b改成a
        r++;
        if(s[r] == 'b') sum++;//新加的字符为b
        while(sum > k && l < r){
            l++;
            if(s[l] == 'b') sum--;//删去的字符为b
        }
        ans = max(ans, r - l);//求max
    }
    cout << ans;//输出
    return 0;
}
```

---

## 作者：gxxjqqiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF676C)

**题目描述：**

给你一个长度为n，只含字符a和b的字符串，求至多改动k个字符后连续相同字符个数的最大值。（好精简的翻译）

**思路**：尺取法。

我们用两个循环，分别模拟尽量改成'a'和尽量改成'b'的情况，记录选定序列的开端选定序列中第一个要被修改的量和序列长度（并更新答案）。当剩余操作次数要＜0时，使现序列长度减去第一个要被修改的量及以前的一截，更新序列开端并重新寻找第一个要被修改的量。

举个例子：
```
10 1
bbabbabbba
```
改成‘a’和改‘b’差不多，这里就只说改成‘b’的情况吧。

定义序列开端为s=1，选定序列中第一个要被修改的量为last=0，序列长度为cnt，答案为ans。字符串先把第0位补上一个东西。

i=1：无需修改，```cnt++;```此时，cnt=1；ans更新；

i=2：无需修改，```cnt++;```此时，cnt=2；ans更新；

i=3：先“修改”，```if(m)m--;```此时，m=0；last之前没有值，现在last=3，cnt继续加1；ans更新；

i=4：无需修改，```cnt++;```此时，cnt=4；ans更新；

i=5：无需修改，```cnt++;```此时，cnt=5；ans更新；

i=6：想修改，但是，m用完了。那就把序列的第一个要修改的值以及它之前的全部干掉，cnt-=(last-s+1)，此时cnt=2；s=（last+1）=4，last从4找起，最终last=6；cnt++，此时cnt=3；m还是0（前面少了一次，现在又用一次）；

i=7~9：cnt连加3；cnt=6；ans更新；

i=10：想修改，但是，m用完了。那就把序列的第一个要修改的值以及它之前的全部干掉，cnt-=(last-s+1)，此时cnt=3；s=（last+1）=7，last从7找起，最终last=10；cnt++，此时cnt=4；m还是0（前面少了一次，现在又用一次）。

最终，ans=6。完美结束。

但是，这个思路在处理m=0的数据时会自动地多处理，导致出错。所以，加个特判，卡掉这种情况即可。

AC Code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
int n,m,m2,s=1,last,cnt,ans;
string st;
int main(){
	cin>>n>>m;
	cin>>st;
	m2=m;st="0"+st;
	for(int i=1;i<=n;i++)
	{
		if(st[i]=='b')
		{
			if(m){m--;if(!last)last=i;}
			else
			{
				if(!m2){cnt=0;continue;}//所谓特判
				cnt-=(last-s+1);
				s=last+1;
				for(int j=s;j<=i;j++)
				if(st[j]=='b'){last=j;break;}
			}
		}//思路见上文
		cnt++;ans=max(ans,cnt);//记答案
	}
	cnt=last=0;m=m2;s=1;
	for(int i=1;i<=n;i++)
	{
		if(st[i]=='a')
		{
			if(m){m--;if(!last)last=i;}
			else
			{
				if(!m2){cnt=0;continue;}
				cnt-=(last-s+1);
				s=last+1;
				for(int j=s;j<=i;j++)
				if(st[j]=='a'){last=j;break;}
			}
		}
		cnt++;ans=max(ans,cnt);
	}
	cout<<ans;
	return 0;
}
```
祝大家早日AC此题。

---

## 作者：zhou_ziyi (赞：1)

### 大致思路

此篇题解采用尺取法：

设定两个指针 $l$ 和 $r$，同时指向第一个字符我们创建两个计数器 `cnt1`  和 `cnt2` 统计当前已更改的字符 $a$ 和 $b$ 数目我们向右移动 $r$。

如果不满足：$cnt1\leq k||cnt2\leq k$ 移动左端点 $l$。

### Code

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
char s[100005];
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", s);
    int l = 0, r = 0, ans = 0;
    int cnt1 = 0, cnt2 = 0;
    while(r < n) {
        if(s[r] == 'a')
            cnt1++;
        else
            cnt2++;
        if(cnt1 <= k || cnt2 <= k)  ans++, r++;
        else {
            if(s[l] == 'a') cnt1--;
            else    cnt2--;
            l++, r++;
        }
    }
    printf("%d", ans);  
    return 0;
} 
```

---

## 作者：Zhou_Wingay (赞：1)

题目已经说了，相同字符需要连续，所以我们用 $left$ 存第一个数的坐标，用 $right$ 存最后一个数的坐标。

用 $a$ 来存这一串里 a 出现的次数，用 $b$ 来存这一串里 b 出现的次数。

根据题目要求，只要 $a$ 和 $b$中有一个小于 $k$ ,这个串就能成立。

如果 $a$ 和 $b$ 均大于 $k$,那我们只需不断将 $left$ 后移即可。

最后就是代码了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
char c[100005];
int main(){
	int i,j;
	cin>>n>>k;
	cin>>c;
	int l=0,r=0,ans=0,a=0,b=0;
	for(;r<=n-1;){
		if(c[r]=='a')a++;//纪录a和b出现的次数。
		if(c[r]=='b')b++;
		if(a<=k||b<=k){ans++;r++;}//如果可以，答案加1
		else{//否则将left往后推
			if(c[l]=='a')a--;
			if(c[l]=='b')b--;
			l++;r++;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：pomelo_nene (赞：1)

尺取法+贪心

## ~~我们教练“出”的一道绝世好题~~

话不多说，出代码：
```cpp
#include<cstdio>
char a[100005];
int main(){
	int n,k;
	scanf("%d %d %s",&n,&k,a);//输入
	int l=0,r=0,ans=0,numa=0,numb=0;//l，r是两个指针（尺取法），ans为答案，numa与numb为a与b的计数器
	while(r<n)
	{
		if(a[r]=='a')	numa++;//若该字符为a，a计数器++
		else	numb++;//否则b计数器++
		if(numa<=k or numb<=k)	ans++,r++;//当还能修改的时候，就更新答案，把答案+1，右指针向右
		else
		{
			if(a[l]=='a')	numa--;//否则a计数器--
			else	numb--;//或者b计数器--
			++l,++r;//左右指针右移
		}
	}
	printf("%d",ans);//输出答案
	return 0;
}
```

就这样XD

---

## 作者：wbw_121124 (赞：0)

[博客园食用](https://www.cnblogs.com/wbw121124/p/17944067)

使用尺取法（双指针法）。

1. 由于字符种类只有 $2$ 种，答案一定是全 a 或全 b。

2. 情况 $1$：全 a 

	快指针循环移动，并统计字符 b 的数量 $cntb$，直到 $cntb$ 即将超过 $k$。

3. 情况 $2$：全 b 

	同上。

4. 答案即为两种情况取到的最大值。

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,cnta,cntb,ans,l,r=-1;
string s;
signed main()
{
	cin>>n>>k>>s;
	while(r<n-1)
	{
		r++;
		if(s[r]=='a')
			cnta++;
		else
			cntb++;
		if(cnta<=k||cntb<=k)
			ans++;
		else
		{
			if(s[l]=='a')
				cnta--;
			else
				cntb--;
			l++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZJMZJM (赞：0)

虽说看起来很难，其实好水的一道题啊。

这道题用贪心+尺取法

尺取的适用条件一般是连续区间

分别只考虑含k个a和含k个b的情况

遍历一遍数组，遇到a更新当前选中的区间a的个数，当超出k个时把左端点放到第一个a的下一位，更新最大值

b也一样

最后取两个最大值中的最大值即可。
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>//头文件 别忘了queue
#define MAXN 100005
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环简写
#pragma GCC optimize(4)
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}//读入优化
char s[MAXN];//字符数组
queue <char> Q;//队列
int main()
{
    int n=read(),k=read();
    scanf("%s",s);//读入
    int ans=0;
    int l=0;
    For(i,0,n-1)//a的遍历
    {
        if(s[i]=='a')
            Q.push(s[i]);
        else if(l<k)
        {
            l++;
            Q.push(s[i]);
        }
        else
        {
            ans=max(ans,(int)Q.size());
            while(!Q.empty()&&Q.front()=='a')
                Q.pop();
            if(!Q.empty())
            {
                Q.pop();
                Q.push(s[i]);
            }
        }
    }
    ans=max(ans,(int)Q.size());//更新
    while(!Q.empty()) Q.pop();
    l=0;
    For(i,0,n-1)//b的遍历
    {
        if(s[i]=='b')
            Q.push(s[i]);
        else if(l<k)
        {
            l++;
            Q.push(s[i]);
        }
        else
        {
            ans=max(ans,(int)Q.size());//更新
            while(!Q.empty()&&Q.front()=='b')
                Q.pop();
            if(!Q.empty())
            {
                Q.pop();
                Q.push(s[i]);
            }
        }
    }
    ans=max(ans,(int)Q.size());//取最大值
    printf("%d\n",ans);
    return 0;
}
```

---

