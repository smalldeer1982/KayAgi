# Grandma Laura and Apples

## 题目描述

Grandma Laura came to the market to sell some apples. During the day she sold all the apples she had. But grandma is old, so she forgot how many apples she had brought to the market.

She precisely remembers she had $ n $ buyers and each of them bought exactly half of the apples she had at the moment of the purchase and also she gave a half of an apple to some of them as a gift (if the number of apples at the moment of purchase was odd), until she sold all the apples she had.

So each buyer took some integral positive number of apples, but maybe he didn't pay for a half of an apple (if the number of apples at the moment of the purchase was odd).

For each buyer grandma remembers if she gave a half of an apple as a gift or not. The cost of an apple is $ p $ (the number $ p $ is even).

Print the total money grandma should have at the end of the day to check if some buyers cheated her.

## 说明/提示

In the first sample at the start of the day the grandma had two apples. First she sold one apple and then she sold a half of the second apple and gave a half of the second apple as a present to the second buyer.

## 样例 #1

### 输入

```
2 10
half
halfplus
```

### 输出

```
15
```

## 样例 #2

### 输入

```
3 10
halfplus
halfplus
halfplus
```

### 输出

```
55
```

# 题解

## 作者：CobaltChloride (赞：21)

```
#include<水的一匹>
#include <bits/stdc++.h>
using namespace std;
long long n,m,apple,money,i;
string s[51];
//本题从结束状态倒推回去即可,求出卖的个数,乘以单价就是答案 
int main(){
    cin>>n>>m;
    m/=2;
    for(i=1;i<=n;i++) cin>>s[i];
    for(i=n;i>=1;i--){
    	apple*=2;
    	if(s[i]=="halfplus") apple+=1;//赠送,但不加钱 
    	money+=apple;
	}
	money*=m;
	cout<<money;
	return 0;
}
```

---

## 作者：DPair (赞：14)

# 【节前语】
这道题明显是恶意评分上去的。不过为了难度统计，你懂得（~~恶意评分还是要有的~~）

# 【思路】
没有算法，直接用我们小学学过的方法模拟。

可以发现，我们应当用**倒推**的方法来计算。然后每次遇到$halfplus$就给当前的苹果数乘二加一，否则乘二。最后把每次卖出的钱加起来就是答案。

# 【代码】

## 太水了懒的写注释
```cpp
#include <bits/stdc++.h>
using namespace std;

long long p, ans, num;
int n;
string s[50];

int main()
{
    scanf("%d%lld", &n, &p);
    p /= 2;
    for (int i = 1;i <= n;i ++)
    {
        cin >> s[i];
    }
    for (int i = n;i >= 1;i --)
    {
        num *= 2;
        if(s[i] == "halfplus") num ++;
        ans += num;
    }
    printf("%lld", ans*p);
}
```


---

## 作者：hexiao (赞：7)

$\color{red}\colorbox{Yellow}{这道题明显是恶意评分！但这不表明我们不可以做!}$ 
好，话不多说，我们来看代码。
```cpp
#include<bits/stdc++.h>//万能库，不懂自己查。
using namespace std;
long long int n,p,apple,sum;
//有n个顾客买苹果，单价p,apple是单个顾客买的，sum是老太太的苹果数量。
string s[100];
int main()
{
    
    cin>>n>>p;
    p/=2;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
    }
    //读入
    for(int i=n;i>=1;i--)
    {
    	//"每个顾客买老太太所拥有苹果的一半。"这句话的意思是老太太的苹果数/2。
        apple*=2;//因为是倒推，所以每一步apple*2		
        if(s[i]=="halfplus") 
        {
            apple++;//(apple+0.5)*2=apple*2+0.5*2=apple*2+1
        }
        sum+=apple;//累加
    }
     cout<<sum*p<<endl;//输出
}

```
本蒟蒻第一次发题解，希望过。

---

## 作者：Aliemo (赞：4)

# so easy
### 这道题是呢么的简单 
## 代码中的一些东西没有用可以略过

## 我用的逆推容易推 half就*2  halfplus就*2+0.5因为最后没有剩余所以ans就=0；  再用ans推出卖了多少钱就是sum 特别好推理解了就很简单
## 剩下的看代码吧



```cpp
#include<cstdio>  //头文件不解释
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
double n;
double p,ans; //苹果和
long long sum;  //钱数
string s[50];  //存储half和halfpuls
inline long long f_pow(long long x,long long y,long long z) {//不用看了...
	long long js=1;
	while(y) {
		if(y&1) js=js*x;
		x=x*x;
		y>>=1;
	}
	return js;
}
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n>>p;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=n;i>=1;i--){//逆推出ans  苹果的总数
		if(s[i]=="half"){
			ans*=2;
		}
		if(s[i]=="halfplus"){
			ans+=0.5;
			ans*=2;
		}
	}
	for(int i=1;i<=n;i++){//顺推出sum  //钱数
		if(s[i]=="half"){
			sum+=(ans/2)*p;
			ans/=2;
		}
		if(s[i]=="halfplus"){
			sum+=(ans/2)*p;
			ans/=2;
			ans-=0.5;
		}
	}
	cout<<sum;//sum就是最后的结果啦QAQ
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```

---

## 作者：幻之陨梦 (赞：1)

**题目大意**：给你n个信息，单价为p，让你算总价为多少。

**解题思路**：在读入的中间加上特判就可以了

ps:不开long long见祖宗
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//将ll定义为long long 
inline ll read(){//快速读入 
    int x=0,k=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') k=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
ll n,m,s,ans;
//n即为题目描述里的n，m即为题目描述里的p 
string str[51];
//定义字符串类型数组 
int main(void){//我就喜欢用void 
    n=read(),m=read();//读入 
    m/=2;
    for(int i=1;i<=n;i++) cin>>str[i];//读入 
    for(int i=n;i>=1;i--){
        s*=2;
        if(str[i]=="halfplus") s++;
        //如果是halfplus这个单词，就赠送但不加钱 
        ans+=s;//ans每次加上s 
    }
    ans*=m;//答案乘以单价 
    printf("%lld",ans);//输出 
}
```

---

## 作者：ViXpop (赞：1)

## 此题非常水

看完题目相信大家第一反应就是模拟（反正本蒟蒻就是这样）

但是左看右看没发现题目给出苹果数量，所以我们没有办法打一个正常的模拟

既然如此，我们可以用小学奥数通过苹果购买情况倒推出苹果数量

最后乘以单价即可

#### 一定要开long long!!!

#### 上代码

```
#include <bits/stdc++.h>
#define mem(i,j) memset(i,j,sizeof(i))
#define Endl printf("\n")
#define int long long//不开long long见祖宗
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e3+5;
int n,p,num,sum;
string s[N];
#undef int
int main(){
    n=read(),p=read()/2;
    for(register int i=1;i<=n;i++)cin>>s[i];
    for(register int i=n;i>=1;i--){//下面是倒推部分
        if(s[i]=="half")num*=2;//不送苹果直接乘2
        else num=num*2+1;//送苹果就加一，因为是送半个苹果，所以倒推时加1
        sum+=num;
    }
    write(sum*p);
    return 0;
}
```
PS：单价一定要除以二，因为倒推出来的苹果数量应该是原数量的两倍（原因太简单了不解释）

---

## 作者：sinsop90 (赞：0)

在AC了这题之后,本笨蒟蒻看了一眼各位巨佬的代码

发现我的代码太笨了

首先将每一次读入的字符串判断是不是多给半个,如果是就将mps[i]赋为true

再通过每一次判定的mps将k复原出来

我们知道最后一个字符串肯定是halfpalf,所以先把kp赋为1,跳过最后一项

如果mps[i]是true,就意味着多给了半个,这时候就是kp = (kp+0.5)*2

其他时候直接*2就行了

在复原过程中,用一个数组将数全部几下(每一次kp的值)

最后再用ans加起来乘上单价就行了

输出ans/2因为每一次记录的买的其实只是1/2

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,p,kp=1;//一大堆东西各有其用,内存大
	long long ans=0;
	char maps[100005];
	bool mps[100005];
	long long msl[100005];
	memset(mps,0,sizeof(mps));
	cin>>n>>p;
	for(int i=1;i<=n;i++){
		cin>>maps;
		if(maps[4]=='p'){
			mps[i] = true;
		}
	}
	msl[n] = 1;
	for(int i=n-1;i>=1;i--){//倒推,时间大
		if(mps[i]){
			kp = (kp+0.5)*2;
		}
		else{
			kp*=2;
		}
		msl[i] = kp;
	}
	for(int i=1;i<=n;i++){
		ans+=msl[i]*p;//最后加起来*单价
	}
	cout<<ans/2<<endl;
}//我太蒟了

```


---

## 作者：shenmadongdong (赞：0)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

这道题用倒推的方法来计算即可。每次遇到halfplus就给当前的苹果数乘二加一，否则就把苹果数乘二。最后把每次卖出的钱加起来乘单价就是答案。

代码：
```
var n,p,num,ans:int64;
    i:longint;
    s:array [1..1000000] of ansistring;
begin
  readln(n,p);
  p:=p div 2;
  for i:=1 to n do readln(s[i]);//读入
  for i:=n downto 1 do
    begin
      num:=num*2;
      if s[i]='halfplus' then inc(num);
      ans:=ans+num;//计算
    end;
  writeln(ans*p);
end.
```

---

## 作者：TCZN (赞：0)

直接进入正题：

此题直接模拟就行

## 大体思路：
倒推出苹果的数量，最后再乘以单价，然后直接输出
### 主要思路
使用倒推的办法，如果遇到halfplus​就加0.5*2（因为奶奶送半个苹果），如果不是halfplus而是half就直接乘以2



```pascal
var
  n:int64; //题目说答案可能会很大，要用int64（那奶奶不是赚翻了？）
  i:longint;
  g,s,p:real; //p要用实型
  a:array[1..123] of string;
begin
 readln(n,p);
  s:=0;g:=0;
   for i:=1 to n do
    readln(a[i]);
     for i:=n downto 1 do  //因为是倒退，所以循环也要倒着
       if a[i]='halfplus' then //如果是halfplus就送半个苹果
        begin
         g:=(g+0.5)*2;//送半个（话说她怎么送？切开来？？）
         s:=s+1;//送的个数
        end
         else g:=g*2;//是half就直接乘2
          writeln((g-s*0.5)*p:0:0); //s*0.5其实就是实际送出去的苹果价格，注意保留整数！因为刚刚我们把这三个数定义为实型
end.
```


---

## 作者：αnonymous (赞：0)

其实这道题数据比较水，用**暴力模拟**也是可以滴
## 核心
其实就是小学数学之倒推,从最后卖完开始,苹果数为0

如果是“halfplus”就先加上0.5再乘2（记得标记送的苹果的个数）

否则，就直接乘2
```cpp
#include <iostream>
using namespace std;
long long n,a[41];
double ans,sum,p;
string s;
int main(){
	int i;
	cin>>n>>p;
	for(i=1;i<=n;i++){
		cin>>s;
		if(s=="halfplus")
			a[i]=2;//"halfplus"标记为2，便于判断
		else
			a[i]=1;
	}
	for(i=n;i>=1;i--)
		if(a[i]==2){//如果是halfplus
			ans=(ans+0.5)*2;//倒推:先加送的半个，再乘2倍
			sum++;//标记总共有多少个送的半个苹果
		}
		else
			ans*=2;//直接乘2
	cout<<(long long)((ans-0.5*sum)*p)<<endl;//ans-0.5*sum就是实际卖出钱的苹果数
	//long long毒瘤,卡我三次，害我三次死得不明不白的
	return 0;
}
```


---

