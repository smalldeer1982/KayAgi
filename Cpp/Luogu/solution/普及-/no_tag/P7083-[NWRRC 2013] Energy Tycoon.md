# [NWRRC 2013] Energy Tycoon

## 题目描述

小 Vasya 正在玩一个新的电脑游戏——回合制策略游戏 `Energy Tycoon`。

游戏的规则很简单：

棋盘上有 $n$ 个槽位排成一行。

有发电厂，一个发电厂占据一个或两个连续的槽位，并产生一个单位的能量。

每回合游戏允许你建造一个新的发电厂，如果你愿意可以将其放在棋盘上。如果没有地方放新的发电厂，你可以移除一些旧的发电厂。

每回合结束后，计算机会计算棋盘上发电厂产生的能量总量并将其加到总分中。

Vasya 已经知道他每回合可以建造的发电厂类型。现在他想知道，他能获得的最大可能分数是多少。你能帮助他吗？

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
21121
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2
12
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
211
```

### 输出

```
4
```

# 题解

## 作者：Wind_Smiled (赞：6)

## 题意
有一行 $n$ 个空位。
有一些能源装置，每个能源装置会占用 $1$ 或 $2$ 个空位，并且每回合产生一个单位的能量。每个回合可以建造一个新的能源装置（也可以不建造）。如果没有地方建新的能源装置，可以拆除一些旧的能源装置。每一回合过后，统计这一回合内所有已经建造的能源装置产生的能量，并将其加到总分中。
现在求可能的最大得分。


------------
### 贪心
因为每一种能源装置产出能量相等，所以在贪心算法中的条件判断式有三个：

1.	尽可能地放置占位为 $1$ 的装置。
2.	若剩余位数为 $0$ 且有一个或以上的占位为 $2$ 的装置，则将一个占位为 $2$ 的装置拆除，并更换为占位为 $1$ 的装置。
3.	若条件 $1,2$ 都不成立，且剩余位数大于等于 $2$，则放置占位为 $2$ 的装置。

用变量 $one,two$ 分别记录占位为 $1,2$ 的装置数，$ans$ 记录总得分，$s$ 记录每回合安装的装置的占位（$s_i$ 访问每一位进行判断，因为题中未给出回合总数）。

$n$ 作为空位总数，可以用自增自减来模拟安装装置后的空位数 ，减去相对应的占位数，对应的种类的个数加一。

对于贪心的条件 $2$ ，我们让条件表达式为：`n==0&&two>=1`，因为若 $n=1$，则还能安装，若 $two \ge 1$ 则可以拆除一个，安装为占位为 $1$ 的装置（在此处会增加 $2$ 个空位，再减少 $1$ 个空位，总空位数会增加 $1$）。

#### ~~毒瘤~~
+	在这个题目里，数据还是挺毒瘤的，~~不开 `long long` 见祖宗。~~

+	因为题中未给出回合总数，要用 `string` 类存储。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,one,two;
string s;
int main(){
	cin>>n>>s;
	for(long long i=0;i<s.size();i++){
		if(s[i]=='1'){
			if(n>=1){
				one++;
				n--;
			}
			else if(n==0&&two>=1){
				two--;
				one++;
				n++;
			}
		}
		else if(s[i]=='2'){
			if(n>=2){
				two++;
				n-=2;
			}
		}
		ans=ans+one+two;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZXY赵显义 (赞：2)

此为蒟蒻的第一篇主题库题解，请放心食用。  
[P7083 \[NWRRC2013\] Energy Tycoon](https://www.luogu.com.cn/problem/P7083)

------------

这道题我用的方法就是 **模拟 + 贪心** 。当然这道题必定是有坑的 ：  
1. 没有开 `long long`。  
2. **回合数** 未知 。所以 ：  
如果你用 `string` ：你目前可以 **不考虑** 这个问题。  
如果你用 `char[]` ：建议你把里面的数字 **弄大亿点**。

------------

**这道题的思路：**  
贪心 $1$：能放占地 $1$ 的能源装置就放。  
贪心 $2$：如果放不了拆掉一个占地 $2$ 的能源装置换上一个占地 $1$ 的能源装置。  
贪心 $3$：在否则就尽可能放置占地 $2$ 的能源装置。

用 $cnt1$ 存储当前占地 $1$ 的能源装置的数量。  
用 $cnt2$ 存储当前占地 $2$ 的能源装置的数量。   
则 占地 $1$ 的能源装置的总占地为 $cnt1$ 。  
而 占地 $2$ 的能源装置的总占地为 $cnt2$ 。  

贪心 $1$ 满足条件： $cnt1+2*cnt2+1≤n$，说明还有放置占地 $1$ 的能源装置的位置，就放置。  
贪心 $2$ 满足条件： $cnt1+2*cnt2+1$ 已经超过 $n$ ，即所有的占地位置，那必然只超出了占地 $1$ 的位置，这时如果之前有占地 $2$ 的能源装置，那么将占地 $2$ 的能源装置换位占地 $1$ 的能源装置，这样空间就刚好了。  
贪心 $3$ 满足条件： 除了以上的条件之外，即完全有空间放置占地 $2$ 的能源装置，就放置。

------------

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,sum,cnt1,cnt2;
string str;
int main(){
	cin>>n>>str;
	for(int i=0;i<str.size();i++){
		if(str[i]=='1')
			if(cnt1+2*cnt2+1<=n) cnt1++;//贪心1：占地1的能源装置增加1
			else if(cnt2) cnt2--,cnt1++;//贪心2：占地2的能源装置减少1，占地1的能源装置增加1（换2为1）
		if(str[i]=='2'&&cnt1+2*cnt2+2<=n) cnt2++;//贪心3 ：占地2的能源装置增加1
		sum+=cnt1+cnt2; 
	}
	return cout<<sum,0;
}
```
无注释：  
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,sum,cnt1,cnt2;
string str;
int main(){
	cin>>n>>str;
	for(int i=0;i<str.size();i++){
		if(str[i]=='1')
			if(cnt1+2*cnt2+1<=n) cnt1++;
			else if(cnt2) cnt2--,cnt1++;
		if(str[i]=='2'&&cnt1+2*cnt2+2<=n) cnt2++;
		sum+=cnt1+cnt2; 
	}
	return cout<<sum,0;
}
```
没用 `string` 用 `char[]` 的同学 ， 你们需要进行如下更改 ：

```cpp
string str;                        改为: const int N=1e6+5;char str[N];
for(int i=0;i<str.size();i++){}    改为: for(int i=0;i<strlen(str);i++){}
```

---

## 作者：Asimplename (赞：1)

## 思路

如果此回合只能用 ``1``，那么如果可以放得下就直接放，如果不能就尽可能拿掉旧的 ``2``（因为每回合都只能产生 $1$ 能量）。如果只能用 ``2``，那么直接放得下就直接放，否则就可以不放。

## 代码

```cpp
#include<iostream>
using namespace std;
int n;
string str; 
long long num1;
long long num2;
long long sum;
long long ans;
int main (){
	cin >> n >> str;
	for(int i = 0; i < str.size(); i ++){
		if(str[i] == '1'){
			if(sum + 1 <= n){
				sum += 1;
				num1 ++;
			}
			else{
				if(num2 != 0){
					sum -= 1;
					num1 ++;
					num2 --;
				}
			}
		}
		else{
			if(sum + 2 <= n){
				sum += 2;
				num2 ++;
			}
		}
		ans += num1 + num2;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：honey_ (赞：1)

## 读题
  简述：给定空位数量和能源装置所占空间，每次可放入或拿掉一个格子，求出最大能得到的分数
## 算法
  模拟+贪心
## 具体思路
  读入一个整数 $n$ 和字符串 $s$ 后，用 $a1,a2$ 分别保存 $1$ 和 $2$ 的数量。   
  遍历字符串 $s$
  * 如果扫描到的字符为 $1$ ：   
    1.如果 $a1+a2*2 \le n$ ,那么 $a1++$;   
    2.否则如果 $a2\ne 0$ ,那么 $a2--,a1++$;
  * 如果扫描到的字符为 $2 \And a1+a2*2 \le n$ ,那么a2++;   
  
  最后再将 $ans$ 增加 $a1+a2$，扫描下一个字符。
  
# Code
```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#define int long long
using namespace std;
int ans,a1,a2,n;
string s;
signed main()
{
    string s;
    int n;
    cin>>n>>s;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='1')
            if(a1+a2*2+1<=n) a1++;  //更改1的数量
            else if(a2) a2--,a1++;
        if(s[i]=='2' && a1+a2*2+2<=n)a2++;  //更改2的数量
        ans+=(a1+a2);  //更改结果
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：S__X (赞：0)

本蒟蒻的的 $17$ 篇题解。

## 题意：
给定位置数量和每个能源装置所占空间，每次可放入或拿掉一个能源装置，求出最大能得到的分数。回合数即等于能源装置个数。

## 分析：
我们用 $a$ 来表示每一回合能放的能源装置；

用 $ans1$ 和 $ans2$ 来存储所占空间分别占 $1$ 个位置和 $2$ 个位置的能源装置的个数；

用 $s$ 表示当前回合已经占用的位置个数。

用 $sum$ 表示当前的分数。

### 贪心分为 $2$ 种状态：
1. 如果 $s+a_i\leq n$，说明当前位置足够放下 $a_i$，那么 $s+=a_i$。
2. 如果 $s+a_i\gt n$，说明当前位置不够放下$a_i$，那么判断 $ans2$ 是否为 $0$。 
	- 如果 $ans2$ 为 $0$，说明每个能源装置都只占用 $1$ 个位置，已经是最优的了，只能进行下一回合；
   - 如果 $ans2\ge 1$，说明有能源装置占用了 $2$ 个位置，我们可以把占用了 $2$ 个位置的 能源装置换成 $a_i$，同时 $s=s-2+1=s-1$。
   
在每一回合结束的时候分数即为 $sum=sum+s-ans2$。

## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
long long n,s,ans1,ans2,sum;//注意开long long
int main() {
	cin>>n>>a;
	for(long long i=0;i<a.length();i++){
		if(a[i]=='1'){//
			if(s+1<=n) {//贪心第一种情况
				s+=1;
			} else if(ans2>0){//第二种情况
				ans2--;
				s-=1;
			}
		} else {
			if(s+2<=n) {//贪心第一种情况
				s+=2;
				ans2++;
			}//由于当前能源装置为2，可以不用更换，已是最优
		}
		sum+=(s-ans2);//统计当前会和所能加的最大分数。
	}
	cout<<sum<<endl;
	return 0;
}
```
三目运算符代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
long long n,s,ans1,ans2,sum;
int main() {
	cin>>n>>a;
	for(long long i=0;i<a.length();i++){
		a[i]=='1'?(s+1<=n?s+=1:(ans2>0?s-=1,ans2--:1),ans1++):(s+2<=n?s+=2,ans2++:1);
		sum+=(s-ans2);
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：Fire_Raku (赞：0)

### 分析题目：

这道题目的翻译让我属实有点懵 qwq，可能也许应该也有看不懂题目的朋友，所以我先讲一下题目的意思吧！   

题目大意： 有容量 $n$ 的工厂，工厂可以装体积为 $1$ 和体积为 $2$ 的发动机，发动机总体积不能超过容量；还有一批发动机，工厂一次回合会装一个发动机，若容量不足时，可以将体积为 $2$ 的发动机拆去，装上这一回合体积为 $1$  的发动机，每台发动机每回合会增加 $1$ 产量，问你：$n$ 回合以后工厂的最大产量是多少？

看完题目，是不是就豁然开朗？其实就是模拟每回合装发动机的过程，尽可能的将容量装满，每回合的产量都能最大化就行了。

模拟过程： 

首先，我们输入 $n$，和字符串 $s$，字符串其实就是把每一回合装什么发动机黏在一起了，循环枚举字符串每一个数字，就是枚举每一回合，如果这一回合是体积为 $1$ 的发动机，我们就判断：如果工厂容量还木有满，我们就直接装上去，体积为 $1$ 的发动机数量加一；如果满了，判断有没有装体积为 $2$ 的发动机，把它拆了，装上新的，反正产量一样，为了以后省容量。如果这一回合是体积为 $2$ 的发动机，那么就判断：容量是否已经不够装了？如果够，装上去，因为能装一个是一个，加产量；如果不够，就，就装不了了呗（无奈。

注意注意事项：  
1. 一定要开 `long long`！！！
2. 一定要开 `long long`！！！
3. 一定要开 `long long`！！！(重要的事情说三遍，我已经踩了 $3$ 次了 QAQ

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std ;
long long a , b , ans ; //a表示已装的体积为1的发动机的数量，b表示已装的体积为2的发动机的数量，ans表示目前总产量
int main(){
	int n ;
	string s ; 
	cin >> n >> s ; 
	for(int i = 0 ; i < s.length() ; i++){ //循环枚举字符串
		if(s[i] == '1'){ //如果是体积为1的发动机
			if(a + b * 2 + 1 <= n) a++ ; //如果a * 1的体积加b * 2加上自己还不大于容量的话，装！
			else if(b){
				b-- ;
				a++ ; //否则，b发动机数量减一，a发动机数量加一
			}
		}
		else if(s[i] == '2'){ //如果是体积为2的发动机
			if(a + b * 2 + 2 <= n) b++ ; //之前发动机总体积加上自己的2还不大于容量的话，装！
		}
		ans += (a + b) ; //加上本回合发动机的总产量
	}
	cout << ans << endl ;
	return 0 ;
}
```
 完结撒花！
 谢谢审核！$\times$ $5$ 辛苦了！

---

## 作者：小小蒟蒻Try (赞：0)

~~水~~橙题一道

不开 `long long` ___

解释一下贪心策略，虽然在每一回合都只可以建造 **一个** 能源装置，然而可以看成每回合把所有的都铲掉再填上。

Q：为什么？

A：因为每回合只有一个量改变。

Q：反例！拆掉一个占 $2$ 空位的，放 $2$ 个占 $1$ 空位的，使能量最大化。

A：这种情况在上一个回合肯定有一个占 $1$ 空位的，所以可以先在上一回合铲掉 $2$ 再放一个 $1$，然后在本回合放一个 $1$。例如：

```
2
211
```

可以这样：

```
第一回合：2
第二回合：2
第三回合：11
```

但按我们的策略也可以：

```
第一回合：2
第二回合：1
第三回合：11
```

于是乎，我们就可以用贪心的思想愉快的解题啦，每回合优先考虑 $1$（贪心），再考虑 $2$。

上（14 行）代码，贪心：

```
#include<bits/stdc++.h>
using namespace std;
long long n,ans,a1,a2,now,l;
//a1表示占1空间装置数，a2亦然，now是每一回合的能量
string str;//处理回合
int main(){
    cin>>n>>str;//输入
    for(int i=0;i<str.length();i++){
        if(str[i]=='1')a1++;
        else a2++;
        now=min(n,a1)+max(min((n-a1)/2,a2),l);
        //表示本回合能量数
        //max是因为防止min((n-a1)/2,a2)<0
        ans+=now;
    }
    cout<<ans;
}
```

---

## 作者：LiuHao2019 (赞：0)

# [[更好的食用体验]](https://www.luogu.com.cn/blog/LiuHao2019/p7083-ti-xie)

简略版（写代码的思路）：

```
if(新建造的能量收集器占用空间为1)｛
	if(没有空间了){
		if(占用空间为2的能量收集器数量 > 0) 拆占用空间2，装占用空间为1;
		else 不建了;
	}
  	else 直接建;
｝
else {
	if(没有空间) 不建了;
  	else 直接建;
}
```

**这题有两个坑点：**

坑点①:不告诉你有多少回合，所以**字符数组要开大一点**

坑点②:答案大小，一定要开**long long**![](https://cdn.luogu.com.cn/upload/image_hosting/juk5l39v.png)

---

算法:**贪心+模拟**，就这么简单

---

首先，如果当前还有足够的空间可以建造本回合的能量收集器，一定得建。但是这是为什么呢？~~这不是显而易见的吗？~~ 如果我们建造，在未来也许(因为空间可能一直足够)会有空间不足的情况。但是我们可以拆了多余的啊！~~真·过河拆桥~~ 因为此时它在为你生成能量，而在未来会被拆，没有影响。但如果你不装它，你就损失了很多能量 ~~由此可见:时间就是金钱~~

---

如果空间不够，怎么办呢？

**拆**啊

如果你要新建占用空间为1的能量收集器，那么只要有占用空间为2的能量收集器，就放心地拆。因为你可以获得同样的能量收益，却腾出了1个空间。

但是如果你要新建占用空间为2的能量收集器，就算了吧。因为如果你拆占用空间为2的能量收集器，是没有用的~~当然如果你愿意就可以拆~~；如果你要拆占用空间为1的能量收集器，更没有用了:你获得了同样的能量，却少了1个剩余空间。

---

[[AC记录]](https://www.luogu.com.cn/record/49350147)

---

$$[AC代码]$$


```
#include<stdio.h>
#include<string.h>
using namespace std;
long long ans;   //答案answer
int now1,now2;   //now1表示建造了多少个占用空间为1的能量收集器，now2表示建造了多少个占用空间为2的能量收集器
char tmp[100000000];//输入，要开大一点
int n;//空间
int main(){
	scanf("%d%s",&n,tmp);//输入
	for(int i = 0;i < strlen(tmp);i ++){
		if(tmp[i] == '1'){//如果占用空间为1
			if(now1+now2*2+1 <= n) now1 ++;//如果有空间，就建造，等同if(n-now1-now2*2 >= 1) now1 ++;
			else if(now2 > 0) now2 --,now1 ++;//如果空间不够并且有占用空间为2的，就拆
		}
		if(tmp[i] == '2' && now1+now2*2+2 <= n) now2 ++;//如果有空间，就建造，等同if(tmp[i] == '2' && n-now1-now2*2 >= 2){now1 ++;now2 --;}
		ans += now1+now2;//能量结算
	}
	printf("%lld\n",ans);//输出
}
```

>kkksc03提醒您，算法千万条，诚信第一条，直接抄题解，棕名两行泪

---

## 作者：Cyx20110930 (赞：0)

我抢到[最优解了。](https://www.luogu.com.cn/record/list?pid=P7083&orderBy=1&status=&page=1)

## 正文

本文我们主要讲一讲做法，顺带卡一下常。

看题面后，其实就是一个策略。

**能建就建，如果满了拆多占地的换少占地的**。

具体是说：

能放 $1$ 就放 $1$。

如果这回合可以放 $1$，并且这回合满了，那就拆 $2$ 放 $1$。

如果可以放 $2$ 且空间足够，那就放 $2$。 

代码就很好写了，放一段。

```cpp

 long long n;
    cin>>n;
    char a;
    long long c=n,ans=0,oneplace=0,twoplace=0;
    while(cin>>a)
    {
        if(c>=1&&a=='1')
        {
            c-=1;
            oneplace++;
        }
        else if(c>=2&&a=='2') 
        {c-=2;twoplace++;}
        else if(c==0&&twoplace!=0&&a=='1')
        {
            c+=1;
            twoplace--;
            oneplace++;
        }
        ans+=oneplace;
        ans+=twoplace;
    }
    cout<<ans;

```

173ms。

然后发现能抢最优解。

于是改代码。

我用 n++ 换 ++n，据说可以快一些。

我又用位运算把 ++n 换成了 n=-~n。

（其实没快多少）

我最快的一次 137ms，还没最优解，于是拿别人的最优解继续卡。

133ms，加了 register int。

开 O2，最优解。

其实我没看见他多 int 了一个大数组，一去掉快多了。

又去掉 s1。

时间再少 5ms，内存少了 72kb。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
string s;
int main()
{
     ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
     int n;
     cin>>n;
     cin>>s;
     int ans=n;
     int sum=0;
     int ans1=0; 
     int ans2=0;
     for(register int i=0;i<s.length();i++)
     {
          
      	    int k=s[i]-'0';
      	    if(k<=ans)
      	    {
      	  	   ans1++;
      	 	   sum+=ans1;
      	   	   if(k==2)
      	       {
      		   	   ans2++;
    		   }
			   ans-=k;
			}
			   else if(k==1)
			   {
			   	     if(ans2>0)
			   	     {
			   	     	   ans2--;
			   	     	   ans++;
			   	     	  
						}
				
						 	 sum+=ans1;
					
			   }
			   else
			   {
			   	 sum+=ans1;
			   }
			 i++;
			 if(i==s.length()) break;
			 k=s[i]-'0';
      	     if(k<=ans)
      	     {
      	     	   ans1++;
      	     	   sum+=ans1;
      	     	   if(k==2)
      	     	   {
      	     	   	   ans2++;
					  }
					  ans-=k;
			   }
			   else if(k==1)
			   {
			   	     if(ans2>0)
			   	     {
			   	     	   ans2--;
			   	     	   ans++;
			   	     	  
						}
				
						 	 sum+=ans1;
					
			   }
			   else
			   {
			   	 sum+=ans1;}
			   	   	 
	    i++;
			 if(i==s.length()) break;
			 k=s[i]-'0';
      	     if(k<=ans)
      	     {
      	     	   ans1++;
      	     	   sum+=ans1;
      	     	   if(k==2)
      	     	   {
      	     	   	   ans2++;
					  }
					  ans-=k;
			   }
			   else if(k==1)
			   {
			   	     if(ans2>0)
			   	     {
			   	     	   ans2--;
			   	     	   ans++;
			   	     	  
						}
				
						 	 sum+=ans1;
					
			   }
			   else
			   {
			   	 sum+=ans1;}
			   	   	 
	  }
	  cout<<sum<<endl;
}
```
### upd:2023.5.279:07 卡常策略。

把后 ++ 改成 前 ++，把 n+1 改成 n=-~n，把循环中 int 改成 register_int，循环展开，再去掉不要的。

---

## 作者：zyl0128_alpha (赞：0)


## 思路
在这里，把 $n$ 视为容量。

如果该字符是 $1$，并且空间足够，就放进来，如果空间不够，就把一个 $2$ 拆掉，放 $1$。

如果该字符是 $2$ 并且空间够，就放 $2$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,ans=0;
	string a;
	cin>>n;
	cin>>a;
	long long x=0,y=0;
	for(int i=0;i<a.size();i++){
		if(a[i]=='1'){
			if(x+y*2+1<=n){
				x++;
			}else if(y){
				y--;
				x++;
			}
		}else if(a[i]=='2'&&x+y*2+2<=n){
			x++;
		}
		ans=ans+x+y;
	}
	cout<<ans;
	return 0;
}
```


---

