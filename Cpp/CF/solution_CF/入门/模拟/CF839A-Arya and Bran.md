# Arya and Bran

## 题目描述

布兰和他的姐姐艾莉亚来自同一所房子。布兰喜欢糖果，所以艾莉亚会给他一些糖果。

一开始，艾莉亚和布兰有0个糖果。一共有n天，在第i天，艾莉亚会在盒子里找到上帝赐予的ai颗糖果。她每天最多能给布兰8块糖。没有给完的糖果可以在以后给他。

你的任务是找出在第n天结束前，布兰最早在第几天可以得到k颗糖果。最后你只要将输出最早天数。如果布兰在第n天也不能得到k颗糖果则输出-1。

## 说明/提示

样例1中，艾莉亚在第二天时可以给布兰3颗糖果。 样例2中，艾莉亚可以在第三天时给布兰总共17颗糖果，因为她每天最多可以给他8颗糖果。
样例3中，艾莉亚不能给布兰9颗糖果，因为她每天最多可以给他8颗糖果，然而只有1天。

## 样例 #1

### 输入

```
2 3
1 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 17
10 10 10
```

### 输出

```
3```

## 样例 #3

### 输入

```
1 9
10
```

### 输出

```
-1```

# 题解

## 作者：Chtholly_L (赞：2)

# 题解 CF839A 【Arya and Bran】

###### ~~大家好，我是奆蒟蒻！今天我又双叒叕来写题解了！~~

拿到这道题，题干看起来特别长，莫急莫慌，其实实质内容没多少，我来给大家解释一下。

**小$A$ 每天会得到 $ai$ 颗糖果，小 $A$ 会给把自己的糖果全部给小 $B$ ，但是每天最多给 $8$ 颗，问多少天小 $B$ 的糖果会超过 $k$ 颗。**



------------

分析一下题，其实就把小 $A$ 假装成一个糖果罐，小 $B$ 每天都会去拿糖，如果糖果罐中的糖超过了 $8$ 颗，小 $B$ 就只会拿 $8$ 颗，如果没有 $8$ 颗，小 $B$ 就会把糖全部拿走。

所以，在代码中只要判断一下超没超过 $8$ 颗就可以了，如果是，小 $B$ 的糖果数加 $8$ ，小 $A$ 的糖减去 $8$ ；如果不是，小 $B$ 加上所有的糖，小 $A$ 就没有糖了。当糖果数达到 $k$ 时，就跳出循环 。

话不多说，上代码

## $Ac$ $Code$

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,k,t,a=0,b=0;  // a 为小 A 的糖， b 为小 B 的
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>t;  //小 A 得到的糖
		a+=t;  //小 A 的糖加上
		if(a>8)  //判断是否超过8
		{
			b+=8;  //如果是，小 B 加8
			a-=8;  //小 A 减8
		}
		else  //如果不是
		{
			b+=a;  //小 B 拿走所有的糖
			a-=a;  //小 A 的糖全部被拿走
		}
		if(b>=k)  //是否达到 k
		{
			cout<<i;  //输出第几天
			return 0;  //结束程序
		}
    }
    cout<<-1;  //没有得到 k 颗糖
    return 0;  //结束程序
}
```
[评测记录](https://www.luogu.com.cn/record/46315167)

[博客食用更佳](https://www.luogu.com.cn/blog/maxsuper/)

###### 博客里还有许多很好的题的题解，欢迎捧场！

---

## 作者：Colead (赞：2)

# CF839A

其实这一题非常的明显，应该使用贪心。

因为这道题的局部最优解就是整体最优解。而且因为每一次Arya给的糖果都是独立的，没有后效性，更加适合使用贪心了。

##### 那么如何贪心？

每一步要给的尽可能多。如果手里面有多于8个糖果，就给8个。否则的话就把手里的全给完！

实现以及细节在代码里：

```
#include<bits/stdc++.h>//c++代码奉上。
using namespace std;
int main()
{
	int nowa=0,god=0,n,k,nowb=0;//nowa表示Arya手中现有的糖果，nowb也是一样，表示Bran手中现有的糖果，god用于记录每一次Arya得到的糖果。n，k如题意。
	cin>>n>>k;
	for(int i=1;i<=n;i++)//重复n天
	{
		cin>>god;//得到了糖果。
		nowa+=god;//手里的糖果增加了！
		nowb+=min(nowa,8);//给尽可能多的糖果（贪心）。
		nowa-=min(nowa,8);//注意这两句不能倒换，不然nowb增加的时候nowa已经改变。
		if(nowb>=k)
		{
			cout<<i<<endl;//得到了足够的糖果。
			return 0;//退出吧。
		}
	}
	cout<<"-1";//还没集齐？算了！
	return 0;//好习惯。
}

```
（自认为）很简洁的代码。希望可以给大家带来帮助。

谢谢大家，我是WT20071112，有问题可以在评论区留言或私信我哦。

再见~

---

## 作者：引领天下 (赞：2)

这题很简单啊，为什么没人做呢？

所以我来贡献一发题解吧

思路：模拟

可以在线做，对于每一个读入的ai，分类讨论

详见代码

```cpp
#include <cstdio>
int n,k,now,ans;
int main(void){
    scanf ("%d%d",&n,&k);//读入不解释
    int i=1;
    for (;i<=n;i++){
        int a;
        scanf ("%d",&a);
        if (a>8)ans+=8,now+=a-8;//分类讨论：ai>8，只能+8，剩下来放到now里，以后备用
        else if (a<=8&&!now)ans+=a;//不足8，且now里没有东西，直接加
        else if (now+a<=8)ans+=now+a,now=0;//之前+现在≤8，直接加，加完归零
        else ans+=8,now-=8-a;//不然+8，继续存
        if (ans>=k)break;//中途ok了就退出
        // printf ("%d %d\n",ans,now);
    }
    if (i>n&&ans<k)printf ("-1");//无解
    //ans<k的用处就在于，防止了正好n天的情况
    else printf ("%d",i);//输出
}
```

---

## 作者：Cloote (赞：1)

这道题很**淼**，题目给了个又长又长的背景，事实上可以简单概括一下：每天你都可以获得`i`颗糖，但你最多只能拿**8**颗，至少需要多少天你才能获得至少`k`颗糖，如果不行就输出`-1`

看到这道题，什么都不要想，直接暴力模拟就行了

每天拿糖可以分成以下两种情况：

1. 可获得的糖加上`i`大于8，现在可获得的糖减去8，已经拿到的糖加上8
2. 可获得的糖加上`i`小于等于8，现在可获得的糖清零，已经拿到的糖加上没有减之前的糖

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int n,k,a[N];
template<typename T>inline void read(T& x)//快读
{
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') f=1,c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	if(f) x=-x;
}
int main()
{
    ios::sync_with_stdio(false);//简单的输入输出优化
    read(n);read(k);
    for(int i=1;i<=n;i++){
    	read(a[i]);
    }
    int sum=0,have=0;//sum是可获得的糖，have是已有的糖
    for(int i=1;i<=n;i++){
    	sum+=a[i];
    	if(sum<8){//如果不够8颗
    		have+=sum;
    		sum=0;
    	}
    	else{//比8颗大
    		have+=8;//拿最多可以拿的8
                           颗
    		sum-=8;
    	}
    	if(have>=k){//如果现在已经有k颗了
    		cout<<i;//直接输出现在的天数
    		return 0;//谁还要break呀，没有人要break
    	}
    }
    cout<<-1;
    return 0;
}
```


---

## 作者：Creroity (赞：1)

我又双叒叕来水题解了！

### **这题其实很简单的：**

我们只需要判断一下就 OK 啦！

对于输入的 $a_i$ ，其实我们不需要数组，因为我们可以开一个 now 变量在存储此时艾莉亚手中的糖果数量，而 a ~~只是个工具数~~，输入一下再存储一下就不需要用了。

然后对于变量 now ，只需要判断此时艾莉亚手中的糖果数是否超过 8 就行了，若超过，就将 now 变量中的 8 个糖果移动到 tot 变量中（此时布兰能得到的糖果数）就可以了。

最后题目要求输出所需天数。

这个简单，我们可以边输入边计算，当这一天布兰手中的糖果数不小于 k 也就是当 $tot \geqslant k$ 时，就可以直接输出此时的 i 并直接结束。

对于无法实现的情况，因为可以实现的时候会在输入到一半的时候直接结束，所以我们就不需要再进行判断，只要程序还能执行到输入完成后，就可以输出 -1 并结束。

#### 一段~~两分钟就能搞定~~的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,now,k,tot;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;//输入 
		now+=a;//计算此时艾莉亚手中的糖果数 
		if(now>8){//如果艾莉亚手中的糖果数大于8 
			tot+=8;//布兰得到8颗糖果 
			now-=8;//记住，艾莉亚将糖果给了布兰，艾莉亚手中就少了8颗糖果 
		}
		else tot+=now,now=0;//否则就将所有糖果给布兰 
		if(tot>=k){//当布兰获得的糖果数超过k时 
			cout<<i;//直接输出i 
			return 0;//结束 
		}
	}
	cout<<-1;//如果n天结束了仍未进入第14~17行的判断就说明布兰获得的糖果不到k，输出-1 
	return 0;//结束 
}
```
###### ~~卑微求赞~~

---

## 作者：codemap (赞：1)

一道纯模拟的简单题,连数组都不需要,只需要注意一些细节

直接上代码
```c
#include<iostream>
using namespace std;
int main()
{
    int n,k,t,i,s=0,r=0;//t是每次输入的,s是已经给的糖,r是留下来还没给的
    cin>>n>>k;
    for(i=1;i<=n;i++)
    {
        cin>>t;//输入
        if(t<=8)//如果小于等于8
        {
            if(t+r<=8)//如果加上还没给的还是小于等于8
            {
                s+=t+r;//就将他们全部给出去
                r=0;//没有还没给的
            }
            else//不然
            {
                s+=8;//只给8个
                r-=8-t;//还没给的减去(8-这次找到的)
            }
        }
        else//如果大于8
        {
            s+=8;//只给8个
            r+=t-8;//还没给的加上(这次找到的-8)
        }
        if(s>=k)//如果已经给出的达到范围了
        {
            cout<<i;//输出次数
            return 0;//结束程序
        }
    }
    cout<<-1;//到最后也没结束就输出-1
    return 0;//结束
}
```
# 不要抄袭

---

## 作者：OdtreePrince (赞：1)

# -模拟-

第一个发题解的神犇，代码有点错乱，恕蒟蒻不敬！

这道题是十分死板的模拟题，纯模拟就能拿满分！

但一些细节要注意，蒟蒻上个代码供大家参考。

# 杜绝抄袭

~~~
#include<bits/stdc++.h>
using namespace std;
int j,n,k,now,sum,a[105];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    j=0;
    while(k>0&&j<n){
       j++;
       now+=a[j];
       if(now>=8) k-=8,now-=8;
       else k-=now,now=0;
    }
    if(j==n&&k>0) cout<<"-1";
    else cout<<j;
    return 0;
}
~~~

---

## 作者：囧仙 (赞：1)

没有Python题解？~~我再来水一发~~

---

题解：

按照题目所说，循环每一天，贪心的给出糖果即可。（能给多少给多少）

```pypy3
n,k=map(int,input().split())
a=list(map(int,input().strip().split()))   # 这是读入一整个数组
j=0;now=0
while k>0 and j<n:
    j=j+1
    now=now+a[j-1]
    if now>=8:                   # 最多送出8个
        k=k-8
        now=now-8
    else:                       # 全部送出
        k=k-now
        now=0
if j==n and k>0:print(-1)              # 不行
else:print(j)                      # 可以
```

---

## 作者：阳歌童圣 (赞：0)

这道题比较简单，可以用一些~~简单的~~方法：模拟。

我用一些朴实的讲法与写法，希望将大家讲懂。

咱们边写边讲，上代码：
```cpp
#include<bits/stdc++.h> // 万能头，但会大幅度增加编译时间。
using namespace std;
int n,k,ans,a[105],num,m;// n,k 如题，ans 为总多余糖果数量，num 为 Bran 的总糖果，m 为总多余糖果与单次糖果的数量，用于单次。因为赋值在函数外，全部都自动赋值0。
int main(){
    cin>>n>>k; 
    for(int i=1;i<=n;i++) cin>>a[i]; // 用 for 循环输入每组糖果数量。
    if(n*8<k){
        cout<<"-1"<<endl;
        return 0;
    } //如果每天都给8个还不够，就直接输出“-1”。
    for(int i=1;i<=n;i++){
        m=ans+a[i];
        if(m<=8){ //如果 Arya 手中的糖果数不多余8个。
            num+=m;
            ans=0; //记得将多余的糖果清0。
        }
        else{ //如果 Arya 手中的糖果数多余8个。
            num+=8;
            ans=m-8; //将多余的糖果放在 ans 里。
        }m=0; //用完就将 m 清空。
        if(num>=k){ //如果 Bran 手中糖果够了。
            cout<<i<<endl; //输出天数。
            return 0; //直接结束程序。*散花*。
        }
    }cout<<"-1"<<endl; //如果 Bran 手中糖果不够。
    return 0; //*完结散花*。
}
```

好了，这道题就是这样了，欢迎指出不足，同学们再见。



---

## 作者：Mikemao666 (赞：0)

直接模拟即可

我的思路是用每天给$Bran$的糖果数减去她的期望数（输入时进行），如果k被减完了就直接输出再break。

### 注意！

-1的情况怎么来的呢？

- 当$8*n<k$时，说明~~每天给她8颗糖也救不了她的贪心~~

所以直接判断+输出-1+$return0$即可

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int k,n,ans;
int main() {
	cin>>n>>k;
  	if(8*n<k){
   	  cout<<"-1";
     return 0;
     }
	for(int i=1;i<=n;++i){//从a[1]开始是为了用a[0]存放多出来的糖
		cin>>a[i];
		a[i]+=a[0];//加上剩下的糖
		if(a[i]<=8){//如果糖不大于8
			ans++;//天数累加
			k-=a[i];
		}else{
			ans++;
			k-=8;//直接减8
			a[0]=a[i]-8;//累加剩下的糖数
		}if(k<=0){
			cout<<ans;
			break;//或者直接return 0;
		}
	}
	return 0;
}
```
完结撒世纪末彼岸花❀

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有n天，你想拿到k个糖果，第i天会落下ai个糖果，但是你最多一天拿8个，问你在至少第几天可以拿到至少k个糖果，如果拿不到则输出-1。

大致思路：On扫一遍，如果ai>8则把多余的数记下来，然后每次都判断一下总糖果数到没到k即可

```
#include<bits/stdc++.h>
using namespace std;
int n,k,a[110],ans=0,num=0,flag=0;

int main()
{	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
	{
		a[i]+=num;
		num=max(0,a[i]-8);
		ans+=min(8,a[i]);
		if(ans>=k && !flag)
			cout<<i<<endl,flag=1;
	}
	if(flag==0)
		cout<<-1<<endl;
	return 0;
} 
```


---

