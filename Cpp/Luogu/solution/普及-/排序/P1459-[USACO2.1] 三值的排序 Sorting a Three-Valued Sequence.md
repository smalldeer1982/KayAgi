# [USACO2.1] 三值的排序 Sorting a Three-Valued Sequence

## 题目描述

排序是一种很频繁的计算任务。现在考虑最多只有三值的排序问题。一个实际的例子是，当我们给某项竞赛的优胜者按金银铜牌排序的时候。在这个任务中可能的值只有三种 $1,2,3$。我们用交换的方法把他排成升序的。

写一个程序计算出，给定的一个 $1,2,3$ 组成的数字序列，排成升序所需的最少交换次数


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 1000$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
9
2
2
1
3
3
3
2
3
1```

### 输出

```
4
```

# 题解

## 作者：Pisces (赞：61)

~~一篇很水的题解~~：

方法解释：找到它的原结果和目标结果，并作差：

原：2 3 1 1

目标：1 1 2 3

差：1 2 -1 -2

此时要交换两个数只需要对差进行改变，如将2和第一个1交换，2的差减1,1的差加1，就都变成0了，最后只需要把差全部变为0即可。

样例解释：

编号：1 2 3 4 5 6 7 8 9

原：2 2 1 3 3 3 2 3 1

目标：1 1 2 2 2 3 3 3 3 //因为要从小到大排

差：1 1 -1 1 1 0 -1 0 -2

将1和3对调，差变为0和0，将2和7对调，差变为0和0，将4和9对调，差变为0和-1，将5和9对调，差变为0和0，共4步。

因此，因尽量使它们‘差’的和尽量接近0，所以就有一种奇特的方法：

统计差为1的个数，这些ans都要+1的，再统计差为2的个数，如果有-2对应ans就+1，没有对应就+2。

下面上代码（在洛谷上过不了，所以别想抄题解，但把数据下下来发现答案都是正确的，在别的oj上也能过）：

```cpp
#include<bits/stdc++.h>
#define f(i,a,b) for(register int i=a;i<=b;++i)
using namespace std;
int p,s,tot,ans,have,q,m;
char a[1005<<1],b;//会读入换行，数组大小要*2
int main()
{
    cin>>m;
    f(i,1,m<<1){//读入
    	if(isdigit(b=getchar())){//判断是否为换行
    		a[++p]=b;//存入
    		if(b=='1'){//无需打排序，直接操作
    			int k=a[++s]=='3';//判断是否为3，如果是3，则差为2
    			ans+=a[s]=='2'+k;//先全部+1，再单独判断有没有对应
    			have+=k;//统计差为2的个数
    		}
    		else tot+=b=='2';//统计2的个数
        } 
    }
    f(i,s+1,s+tot){//目标结果为2的部分
        ans+=a[i]=='3';//统计差为1的个数
    }
    f(i,s+tot+1,p){//目标结果为3的部分
        q+=a[i]=='1';//统计差为-2的个数
    }
    cout<<ans+((have>q)?have-q:0)<<endl;//把没有-2对应的2的部分加上
    return 0;
}
```

本人（蒟蒻）第一次发题解，但好像~~时间复杂度好像还蛮低的~~

---

## 作者：ABCDXYZ (赞：40)

这道题不是太难，但思考过程也不简单。


思路的话，简单交代一下：


因为只有三种数，所以只要交换两种数，第三种数就自然排列好了

如果存在一个1在2的位置，并存在一个2在1的位置上，优先交换这一对1和2，就能做到最优


废话不多说，上代码！：


```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int a[1010],flag[1010];
int times_1,times_2,times_3,ans=0,n;
void draw( ){
    for(int i=1;i<=times_1;i++)
        flag[i]=1;
    for(int i=times_1+1;i<=times_2+times_1;i++)
        flag[i]=2;
    for(int i=times_2+times_1+1;i<=n;i++)
        flag[i]=3;//flag数组标记本来应该出现的数字 
}
void Find( ){
    for(int i=1;i<=n;i++){
        if(a[i]==1)times_1++;
        else if(a[i]==2)times_2++;
        else if(a[i]==3)times_3++;
    }//1,2,3分别应该出现的次数 
    draw();
    return;
}
int main( ){
    int m,j,k,i;
    int swap1=0,swap2=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);    
    Find();
    for(i=1;i<=n;i++){
        if(flag[i]==1 && a[i]!=1)
            ans++;
        if(flag[i]==2 && a[i]!=2)
            ans++;
        //此时的ans是至多花费的次数 
        if(flag[i]==1 && a[i]==2)
            swap1++;
        if(flag[i]==2 && a[i]==1)
            swap2++;
    }
    ans-=min(swap1,swap2);
    //min(swap1,swap2)其实是利用容斥原理求出如果有一个1在2的位置上同时
    //存在一个2在1的位置上，可以省下的交换次数 
    printf("%d",ans);
    return 0;
}
```

---

## 作者：liaohaoping (赞：20)

好难的样子QAQ，问了[Lynking大佬](https://lynking.blog.luogu.org/)才知道其实是一道贪心，统计1,2,3的个数，那么排好序的一定是分为三个区间，那么当某数位置错误时，有以下几种情况：

1、一个数字1跑到了区间2，同时区间2中的一个数字2跑到了区间1

2、一个数字1跑到了区间3，同时区间3中的一个数字3跑到了区间1

3、一个数字2跑到了区间3，同时区间3中的一个数字3跑到了区间2

4、一个数字1跑到了区间2，同时区间2中的一个数字2跑到了区间3，区间3中的一个数字3跑到了区间1

5、一个数字1跑到了区间3，同时区间3中的一个数字3跑到了区间2，区间2中的一个数字2跑到了区间1

很明显，前三种需要交换一次，第四、五种需要交换两次，可以先贪心找前三种交换，再找还有几个数未归位，这时由于只会剩下第四、五种情况，三个数为一组，每组需交换两次，所以答案为：前三种交换次数+未归位的数的个数×三分之二

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int a[1100],s[4];
int main()
{
	int n=read();
	for(register int i=1;i<=n;++i)a[i]=read(),++s[a[i]];
	s[2]+=s[1];int ans=0;
	for(register int i=1;i<=s[1];++i)
	{
		if(a[i]!=2)continue;
		for(register int j=s[1]+1;j<=s[2];++j)if(a[j]==1){swap(a[i],a[j]),++ans;break;}
	}
	for(register int i=1;i<=s[1];++i)
	{
		if(a[i]!=3)continue;
		for(register int j=s[2]+1;j<=n;++j)if(a[j]==1){swap(a[i],a[j]),++ans;break;}
	}
	for(register int i=s[1]+1;i<=s[2];++i)
	{
		if(a[i]!=3)continue;
		for(register int j=s[2]+1;j<=n;++j)if(a[j]==2){swap(a[i],a[j]),++ans;break;}
	}
	int ss=0;
	for(register int i=1;i<=s[1];++i)if(a[i]!=1)++ss;
	for(register int i=s[1]+1;i<=s[2];++i)if(a[i]!=2)++ss;
	for(register int i=s[2]+1;i<=n;++i)if(a[i]!=3)++ss;
	printf("%d\n",ans+ss*2/3);
	return 0;
}
```

---

## 作者：Vimin (赞：17)

# 题目传送[P1459](https://www.luogu.org/problem/P1459)
## 思路
- 贪心，把原始数据按三个区间进行排序，第一个区间不是1的数肯定要和后两个区间的1交换。大数尽量往后换，小数往前换的答案优
- 神奇的解法  把数据排序后和原位置上的数据做差，结果只有$-2,2,-1,1$,  

- $-1,1$和 $-2,2$这种情况只要交换一次，而$-1,-1,2$或$1,1,-2$这种情况必须要两次。那么，我们统记$-1,1,-2,2$的个数为$one,two,tre,fou$ 
- 答案是$max(one,two)+min(tre,fou)$
- 为什么呢？ 两个$-1$组合一个$2$ ,那么$one-two$(假设是正的）的$\frac{1}{2}$，是这种情况的个数，这种情况有必须换$2$次，所以$*2 $，答案直接是差值再加上原先的配好对的
## 代码
```
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,one,two,tre,fou,ans;
int a[1005],num[1005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		num[a[i]]++;
	}
	for(int i=1;i<=num[1];i++) a[i]-=1;
	for(int i=num[1]+1;i<=num[1]+num[2];i++) a[i]-=2;
	for(int i=num[1]+num[2]+1;i<=n;i++) a[i]-=3;
	for(int i=1;i<=n;i++) 
	  if(a[i]==-1) one++;
	  else if(a[i]==1) two++;
	  else if(a[i]==2) tre++;
	  else if(a[i]==-2)fou++;
	ans=max(one,two)+min(tre,fou);
	cout<<ans;
	return 0;
}
```

---

## 作者：鹭天 (赞：9)

###我们可以从题目中的一个条件入手：

#只有1,2和3

##既然如此，我们就知道将这个序列排序好后肯定是这么一个模式:1 1 1……2 2 2……3 3 3……

#那么根据这个模式，我们可以将序列分成三段，第一段保存1，第二段保存2，第三段保存3

###然后就先从第一段中找到2，与第二段中的1交换(如果有的话)，在找到3，与第三段中的1交换(如果有的话)，以此类推

那么代码如下:

```cpp
#include<bits/stdc++.h>
using nemespace std;
int a[1005],s[4]={0};//s[i]表示数字i出现的次数
int main(){ 
    int n,sum=0; 
        scanf("%d",&n);
        for(int i=1;i<=n;i++){ 
            scanf("%d",&a[i]);
            s[a[i]]++;
        } 
        int z=s[1]+1,y=n;//注意这一步
        for(int i=1;i<=s[1];i++){
            if(a[i]==2){//如果本该有1的位置出现了2
                while(a[z]!=1)z++;
                int t=a[i];a[i]=a[z]; a[z]=t; 
                sum++; 
        }else if(a[i]==3){//如果本该有1的位置出现了3
            while(a[y]!=1)y--;
            int t=a[i]; a[i]=a[y]; a[y]=t; 
            sum++; 
        }
    } 
    for(int i=s[1]+1;i<=s[1]+s[2];i++) 
    if(a[i]==3)sum++;//如果本该有2的位置出现了3
    printf("%d",sum); 
    return 0; 
}
```
..
#小心直接复制掉坑~~


---

## 作者：zhouwc (赞：6)

#Pascal


看到写此题题解的大神众多，于是心血来潮（虽然我的水平不高）

对于这一道题来说，我的算法是这样的（在我的程序中就不一一说明了）：

首先，我先在b数组中把正确的序列给排列出来，方便接下来的比较。

###第一次扫描（这里用x，y两个数）

如果找到x与y两个数交换位置后，两个数都可以到正确的位置，那么就进行交换。

###第二次扫描（这里用x，y两个数）

如果找到x与y两个数交换位置后，其中的1个数可以到正确的位置，那就进行交换。

在两次扫描后，便可以输出正确的解


下面附上pascal AC 代码

```cpp
var n,i,j,k,t:longint;
    a,b:array[1..1001]of longint;
    l:array[1..3]of longint;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(a[i]);
    if a[i]=1 then l[1]:=l[1]+1;
    if a[i]=2 then l[2]:=l[2]+1;
    if a[i]=3 then l[3]:=l[3]+1;
  end;
  for i:=1 to l[1] do b[i]:=1;
  for i:=l[1]+1 to l[1]+l[2] do b[i]:=2;
  for i:=l[1]+l[2]+1 to n do b[i]:=3;
  for i:=1 to n-1 do
  for j:=i+1 to n do
    if (a[i]<>b[i]) and (a[j]<>b[j]) and (a[j]=b[i]) and (a[i]=b[j]) then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      k:=k+1;
    end;
  for i:=1 to n-1 do
  for j:=i+1 to n do
  if (a[i]<>b[i]) and (a[j]<>b[j]) and ((a[j]=b[i]) or (a[i]=b[j])) then
  begin
    t:=a[i]; a[i]:=a[j]; a[j]:=t;
    k:=k+1;
  end;
  writeln(k);
end.
```
如有错误，还请指出。


---

## 作者：Sor4 (赞：4)

//贪心方法：为了使交换次数最少，就必须要使每次交换的成效最大，





        
    
    
```cpp
//即交换一次要使尽可能多的字母归位。
#include<cstdio>
using namespace std;
int a[1010];
int main()
{
    int k=1,p=0,r,n,A=0,B=0,C=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {scanf("%d",&a[i]);
    if(a[i]==1) A++;//计算个数 
    if(a[i]==2) B++;
    if(a[i]==3) C++;}//1:1~A   2:A+1~A+B  3:A+B+1~A+B+C(范围)
    //！！重点：先把1全部归位，归位时，如果1的区间有2,2的区间有1，交换一次相当于两次，交换。
    //1,3交换同理。之后，再把不能最优交换的进行交换 
    for(int i=1;i<=A;i++)
    {
        if(a[i]==2)
        {
            for(int j=A+1;j<=A+B;j++)
            {
                if(a[j]==1)
                {
                    r=a[i];
                    a[i]=a[j];
                    a[j]=r;
                    p++;
                    break;
                }
            }
        }
        if(a[i]==3)
        {
            for(int j=A+B+1;j<=A+B+C;j++)
            {
                if(a[j]==1)
                {
                    r=a[i];
                    a[i]=a[j];
                    a[j]=r;
                    p++;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=A;i++)
    {
        if(a[i]!=1)
        {for(int j=A+1;j<=A+B+C;j++)
        if(a[j]==1)
                {
                    r=a[i];
                    a[i]=a[j];
                    a[j]=r;
                    p++;
                    break;
                }
        }
    }
    //此时，1已经用最少步数归位，交换2、3变得相对简单。 
    for(int i=A+1;i<=A+B;i++)
    {
        if(a[i]==3)
        {
        for(int j=A+B+1;j<=A+B+C;j++)
        if(a[j]==2)
                {
                    r=a[i];
                    a[i]=a[j];
                    a[j]=r;
                    p++;
                    break;
                }
        }
    }
    printf("%d",p);
    return 0;
}
```

---

## 作者：楯山文乃 (赞：4)

首先 如果两数位置都错了，并且交换后都在正确的位置，这一次交换肯定是必然的；

接着 跑一遍 把所有的符合上述条件的数交换回来 每次交换ans++；

最后 剩下的就是3个数的位置都是错的，也可以通过两次交换达到正确位置 每次交换ans+=2；

（其实可以不用交换，就检查一下在1的位置上有多少个不是1的，乘2即可）


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
int n,i,ans,sum=0;
int a[2000],b[2000],f[10][10];
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++){//读入 
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1); 
    for(i=1;i<=n;i++) f[b[i]][a[i]]++;
    ans=min(f[1][2],f[2][1]);//判断两数位置并交换 
    f[1][2]-=ans; f[2][1]-=ans;
    sum+=ans;
    ans=min(f[1][3],f[3][1]);
    f[1][3]-=ans; f[3][1]-=ans;
    sum+=ans;
    ans=min(f[2][3],f[3][2]);
    f[2][3]-=ans; f[3][2]-=ans;
    sum+=ans;
    sum+=max(f[1][2],f[2][1])*2;//如果三数位置都是错误的，那么进行两次交换使它们位置正确也必定最优
    printf("%d\n",sum);
    return 0;
}

```

---

## 作者：kevin_y (赞：3)

此题思路如下：

1. 先算出1,2,3出现的个数，分好类
2. 再把2 2 1 3 3 3 2 3 1（本题样例）这样的数，每个减去最后要变成的数（例题是要减去1 1 2 2 2 3 3 3 3），要变成1 -1 1 -1 -1 0 1 0 2（保存在b[]里）
3. 记录1,-1,2,-2出现次数（只会有1，-1,2，-2,0这四个数，0不用记）
4. 最后一步很关键，max(q1,w1)+min(q2,w2)。-1,1一次可以换过来，-2,2也是一次换过来，-1,-1,2或1,1,-2要换两次。所以取1和-1出现次数的最大数加上2和-2出现次数的最小数，就是答案。（2与-2出现次数的差，肯定是1与-1出现次数的差的二分之一，取q1,w1最大数加上q2,w2最小数即可）
```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
int main(){
	int n,a[1001],b[1001],i,a1=0,a2=0,a3=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1)a1++;
		if(a[i]==2)a2++;
		if(a[i]==3)a3++;
	}//第一步
	for(i=1;i<=n;i++){
		if(a1>=i)b[i]=1-a[i];
		if(a1+a2>=i&&i>a1)b[i]=2-a[i];
		if(a1+a2+a3>=i&&i>a2+a1)b[i]=3-a[i];
	}//第二部
	int q1=0,q2=0,w1=0,w2=0;//q1存1，q2存2，w1存-1，w2存-2
	for(i=1;i<=n;i++){
		if(b[i]==1)q1++;
		if(b[i]==-1)w1++;
		if(b[i]==2)q2++;
		if(b[i]==-2)w2++;
	}//第三部
	cout<<max(q1,w1)+min(q2,w2);//第四部
} 
```


---

## 作者：Jerx2y (赞：2)

## ----------------Greedy---------------
这道题想到的肯定是贪心。因为要你求最少的交换次数，那么对此贪心策略为：统计1,2,3的个数，每次交换最好是把它放入它本来的位置中（它在排好的序列中的位置，比如说这个序列中1有10个，2有4个，3有6个，那么1的位置就是1～10，2是11～14，3是15～20），这样即可实现最少的交换次数。
具体代码：
```cpp
#include <algorithm>
#include <iostream>//头文件
#include <cstdio>//头文件
using namespace std;//用命名空间std
const int MAXN = 1010;//定义常数
int a[MAXN];
int N;
int num[4];
int ans = 0;
int main()
{
	freopen("sort3.in","r",stdin);
	freopen("sort3.out","w",stdout);
	scanf("%d",&N);
	for(int i = 1;i <= N;i ++){
		scanf("%d",&a[i]);
		num[a[i]]++;
	}
	num[2] = num[1]+num[2];
	num[3] = num[1]+num[2]+num[3];
	for(int i = N; i > num[2]; i--){
		if(a[i] == 1){
			bool l = 1;
			for(int k = 1; k <= num[1]; k++)
				if(a[k] == 3){
					swap(a[k],a[i]);
					l = 0;ans++;
					break;
				}
			if(l)
				for(int k = 1;k <= num[2]; k++){
					if(a[k] != 1){
						swap(a[k],a[i]);
						ans++;
						break;
					}
				}
		}
		if(a[i] == 2){
			bool l = 1;
			for(int k = num[1]+1; k <= num[2]; k++)
				if(a[k] == 3){
					swap(a[k],a[i]);
					ans++;
					l = 0;
					break;
				}
			if(l)
				for(int k = 1; k <= num[1]; k++)
					if(a[k] == 3){
						ans ++;
						swap(a[k],a[i]);
						break;
					}
		}
	}
	for(int i = num[2]; i >= num[1]+1; i--){
		if(a[i] == 1)
			for(int k = 1; k <= num[1]; k++)
				if(a[k] == 2){
					swap(a[k],a[i]);
					ans++;
					break;
				}
	}
	printf("%d\n",ans);
	return 0;
}
```
写的貌似有点长……

---

## 作者：「QQ红包」 (赞：2)

题解 by：redbag

题解地址：[http://redbag.duapp.com/?p=1158](http://redbag.duapp.com/?p=1158)

这里上代码，有注释。

说明见[原题解](http://redbag.duapp.com/?p=1158)。

     
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
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n;
int i,j,sum;
int a[1010],b[4]={0},c[4][4];//c[i][j]在区间段i内j的个数 
int main() 
{
    freopen("sort3.in","r",stdin);
    freopen("sort3.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);//读入 
        b[a[i]]++;//统计个数 
    } 
    for (j=1;j<=b[1];j++)//数字1所在的区间段 
        c[1][a[j]]++;//统计 
    for (j=b[1]+1;j<=b[1]+b[2];j++)//数字2所在的区间段 
        c[2][a[j]]++;//统计 
    for (j=b[1]+b[2]+1;j<=b[1]+b[2]+b[3];j++)//数字3所在的区间段 
        c[3][a[j]]++;//统计 
    int haha=min(c[1][2],c[2][1]);
    sum=min(c[1][2],c[2][1]);//printf("%d  ",sum);
    //交换次数，先2这个区间段的1和1这个区间段的2交换
    c[1][2]-=haha;
    c[2][1]-=haha;
    sum+=min(c[2][3],c[3][2]);// printf("%d  ",sum);
    //交换在2这个区间段的3，和在3这个区间段的2。 
    haha=min(c[2][3],c[3][2]);
    c[2][3]-=haha;
    c[3][2]-=haha;
    sum+=min(c[1][3],c[3][1]);//printf("%d  ====",sum);
    //交换在1这个区间段的3，和在3这个区间段的1。
    haha=min(c[1][3],c[3][1]);
    c[1][3]-=haha;
    c[3][1]-=haha;
    sum=sum+(c[1][2]+c[2][1]+c[2][3]+c[3][2]+c[1][3]+c[3][1])*2/3;
    cout<<sum<<endl; 
    return 0;
}
```

---

## 作者：泠小毒 (赞：1)

# 三值的排序

排序是一种很频繁的计算任务。现在考虑最多只有三值的排序问题。一个实际的例子是，当我们给某项竞赛的优胜者按金银铜牌排序的时候。在这个任务中可能的值只有三种1，2和3。我们用交换的方法把他排成升序的。

写一个程序计算出，给定的一个1,2,3组成的数字序列，排成升序所需的最少交换次数

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/luogu-P1459/)

## 解法

这里给出一种玄妙的解法，统计每种数字出现次数，可以构造三个区间

先考虑最优解，优先交换一次能使2个数字到位的情况

比如在第一段区间里的2和在第二段区间里的1交换

还有1和3，2和3这两种可能

之后会发现，没扫到的只有可能是交换两次能使3个数字到位的情况

只要在第一个区间里扫不是1的数，每个会对答案造成2的贡献

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010],sum[10],ans;
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i],sum[a[i]]++;
	for(int i=1;i<=sum[1];i++)
		for(int j=sum[1]+1;j<=sum[1]+sum[2];j++)
			if(a[i]==2&&a[j]==1)
				swap(a[i],a[j]),ans++;
	for(int i=1;i<=sum[1];i++)
		for(int j=sum[1]+sum[2]+1;j<=n;j++)
			if(a[i]==3&&a[j]==1)
				swap(a[i],a[j]),ans++;
	for(int i=sum[1]+1;i<=sum[1]+sum[2];i++)
		for(int j=sum[1]+sum[2]+1;j<=n;j++)
			if(a[i]==3&&a[j]==2)
				swap(a[i],a[j]),ans++;
	for(int i=1;i<=sum[1];i++)
		if(a[i]!=1)
			ans+=2;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

有以下几种情况：

1、一个数字1跑到了区间2，同时区间2中的一个数字2跑到了区间1

2、一个数字1跑到了区间3，同时区间3中的一个数字3跑到了区间1

3、一个数字2跑到了区间3，同时区间3中的一个数字3跑到了区间2

4、一个数字1跑到了区间2，同时区间2中的一个数字2跑到了区间3，区间3中的一个数字3跑到了区间1

5、一个数字1跑到了区间3，同时区间3中的一个数字3跑到了区间2，区间2中的一个数字2跑到了区间1


很明显，前三种需要交换一次，第四、五种需要交换两

次，可以先贪心找前三种交换，再找还有几个数未归位，

这时由于只会剩下第四、五种情况，三个数为一组，每组

需交换两次，所以答案为：前三种交换次数+未归位的数的

个数×三分之二

```cpp
#include<cstdio>
using namespace std;
int a[1100],s[4];
int main()
{
    int i,j,n;scanf("%d",&n);
    for( i=1;i<=n;i++){scanf("%d",&a[i]);s[a[i]]++;}
    s[2]+=s[1];int ans=0;
    for(i=1;i<=s[1];i++)
    {
        if(a[i]!=2)continue;
        for(j=s[1]+1;j<=s[2];j++)if(a[j]==1){int t=a[i];a[i]=a[j];a[j]=t;ans++;break;}
    }
    for(i=1;i<=s[1];i++)
    {
        if(a[i]!=3)continue;
        for( j=s[2]+1;j<=n;j++)if(a[j]==1){int t=a[i];a[i]=a[j];a[j]=t;++ans;break;}
    }
    for(i=s[1]+1;i<=s[2];i++)
    {
        if(a[i]!=3)continue;
        for(j=s[2]+1;j<=n;j++)if(a[j]==2){int t=a[i];a[i]=a[j];a[j]=t;++ans;break;}
    }
    int ss=0;
    for(i=1;i<=s[1];i++) if(a[i]!=1)ss++;
    for(i=s[1]+1;i<=s[2];i++) if(a[i]!=2)ss++;
    for(i=s[2]+1;i<=n;i++) if(a[i]!=3)ss++;
    printf("%d\n",ans+ss*2/3);
    return 0;
}
```

---

## 作者：爱喝敌敌畏 (赞：1)

这道题真的真的好困~~（jian）难（jian）~~

作为一个蒟蒻，我不会线段树什么的，于是用模拟，先模拟1、2、3各有多少个，发现1区间的2与2区间的1交换，发现1区间的3与3区间的1交换，发现2区间的3与3区间的2交换。

   剩下的3个区间内的无法一次交换的数也只用两次交换就可以把无法一次交换的三个数换了。
   
   ```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using  namespace  std;
struct  node
{
	int  a[5];
}b[5];
int  c[21000],n,d[5];
inline  int  mymin(int  x,int  y){return  x<y?x:y;}
int  main()
{
	scanf("%d",&n);
	for(int  i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		d[c[i]]++;/*计算区间*/
	}
	for(int  i=1;i<=d[1];i++)b[1].a[c[i]]++;/*计算区间内各有多少数*/ 
	for(int  i=d[1]+1;i<=d[1]+d[2];i++)b[2].a[c[i]]++;/*计算区间内各有多少数*/ 
	for(int  i=d[1]+d[2]+1;i<=d[1]+d[2]+d[3];i++)b[3].a[c[i]]++;/*计算区间内各有多少数*/ 
	printf("%d\n",mymin(b[1].a[2],b[2].a[1])+mymin(b[1].a[3],b[3].a[1])+mymin(b[2].a[3],b[3].a[2])/*一次交换*/+abs(b[1].a[2]-b[2].a[1])*2/*二次交换*/);
	return  0;
}
```

---

## 作者：Mark_ZZY (赞：0)

先排序，存入b数组，然后做一个类似于图的数组，连接原点和现点。

对于求ans，

1.只需加min(bian[i][j],bian[j][i])                          -->即求交换两点的次数

2.做完所有的1操作后，ans加2\*max(bian[i][j])(i!=j)-->即求交换三点的的次数

时间复杂度(nlogn)

核心算法O(3\*3)-->自己算

hehe
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
    int a[1001],b[1001];
    int bian[4][4];
    int n,ans=0;
int min(int x,int y) 
{
    return x<y?x:y;
}
int max(int x,int y)
{
    return x>y?x:y;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    //原点连现点
    int t=2147483647;
    for(int i=1;i<=n;i++)
        bian[a[i]][b[i]]++;
    /*for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
            printf("%d ",bian[i][j]);
        printf("\n");
    }*/
    for(int i=1;i<=3;i++)
        for(int j=i+1;j<=3;j++)
        {
            t=min(bian[i][j],bian[j][i]);
            bian[i][j]-=t;
            bian[j][i]-=t;
            ans+=t;
        }
    t=-2147483647;
    for(int i=1;i<=3;i++)
    {
        for(int j=i+1;j<=3;j++)
        {
            t=max(t,bian[i][j]);
            //printf("%d ",bian[i][j]);
        }
        //printf("\n");
    }
    printf("%d",ans+t*2);
}
```

---

## 作者：罗旅洲 (赞：0)

    
    
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int a[1010],s[5],p[5];        //a存储数字,s存储出现的次数,p存储不要交换的数字 
int main(){
    int i,j,k,m,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[a[i]]++;                    //记录每个数出现的次数 
    }
                                    //只需将1,3位置枚举，2就也会自然排好 
    for(i=1;i<=s[1];i++){
        if(a[i]==1)p[1]++;
        if(a[i]==3)p[4]++;        //p[4]表示3在1的区域 
    }
    for(i=n;i>=n-s[3]+1;i--){
        if(a[i]==3)p[3]++;
        if(a[i]==1)p[5]++;         //p[5]表示1在3的区域 
    }
    int ans=(s[1]-p[1])+(s[3]-p[3])-min(p[4],p[5]);//1,3互换就可以实现最小次数 
    printf("%d",ans);
    return 0;
}

```

---

## 作者：Skywalker_David (赞：0)

算法：排序后的序列分为三个部分：排序后应存储1的部分，排序后应存储2的部分和排序后应存储3的部分，贪心排序法应交换尽量多的交换后位置正确的（2，1）、（3，1）和（3，2）数对。当这些数对交换完毕后，再交换进行两次交换后位置正确的（1，2，3）三个数。

 
分析：很明显，每一次交换都可以改变两个数的位置，若经过一次交换以后，两个数的位置都由错误变为了正确，那么它必定最优。同时我们还可发现，经过两次交换后，我们可以随意改变3个数的位置。那么如果存在三个数恰好为1，2和3，且位置都是错误的，那么进行两次交换使它们位置正确也必定最优。有由于该题具有最优子结构性质，我们的贪心算法成立

 
程序：

```cpp
var a:array[1..1000] of integer; 
    f:array[1..3,1..3] of integer; 
    b:array[1..3] of integer; 
    n,i,j,t,p:integer; 
begin 
 readln(n); 
 for i:=1 to n do readln(a[i]); 
 fillchar(f,sizeof(f),0); 
 for i:=1 to n do inc(b[a[i]]); 
 b[2]:=b[2]+b[1]; 
 b[3]:=n; 
 t:=0; 
 for i:=1 to n do 
  if i<=b[1] then inc(f[1,a[i]]) else 
   if i<=b[2] then inc(f[2,a[i]]) else 
    if i<=b[3] then inc(f[3,a[i]]); 
 for i:=1 to 2 do 
  for j:=i+1 to 3 do 
   begin 
    if f[i,j]>f[j,i] then p:=f[j,i] else p:=f[i,j]; 
    t:=t+p; 
    if f[i,j]-p>=0 then f[i,j]:=f[i,j]-p; 
    if f[j,i]-p>=0 then f[j,i]:=f[j,i]-p; 
   end; 
 t:=t+(f[1,2]+f[1,3]) shl 1; 
 writeln(t); 
end.
```

---

## 作者：Ayano (赞：0)

整体思路讲一下 代码比较简单 贪心要求1、2的位置直接分配好，开始扫 里面有3就一定要交换，然后再单独看1、2各自的预留位置，1中有2交换，2中有1交换，最后交换次数求最少的即可



    
   
    
    
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int count[4],ex[4],medal[1001];
int main()
{
    int x,n;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>x;
        count[x]++;
        medal[i]=x;
    }
    for (int i=1;i<=count[1]+count[2];i++)
    {
        if (medal[i]==3) ex[3]++;
        else if (medal[i]==2 && i<=count[1]) 
        ex[1]++;
        else if (medal[i]==1 && i>count[1]) 
        ex[2]++;
    }
    cout<<ex[3]+(ex[1]>ex[2]?ex[1]:ex[2]);
    return 0;
}
```

---

## 作者：YczSS (赞：0)


我们用a[i,j]表示在i的位置上j的个数，比如a[2,1]=5就表示排好序后，上面应该是2，但现在被1占领的位置个数是5。 先贪心到不能两值内部交换。


那么操作之后不会存在a[2,1]>0和a[2,3]>0同时成立的现象。


反证法:比如交换之后a[2,1]>0,且a[2,3]>0则在1的位置上只能有3(1和2能内部相抵的已经全部抵消了),3的位置上只能有1(同理),那么1和3又可以内部交换了，与假设矛盾。得证。


还有最后3值交换是乘2，而不是乘3。

 
```cpp
const
  maxn=1000;
var
  a,b:array[1..maxn]of byte;
  c:array[1..3]of integer;
  i,j,n,tmp,tot:integer;
begin
  assign(input,'sort3.in'); reset(input);
  assign(output,'sort3.out'); rewrite(output);
  readln(n);
  fillchar(c,sizeof(c),0);
  for i:=1 to n do
    begin
      readln(a[i]);
      inc(c[a[i]]);
    end;
  for i:=1 to c[1] do b[i]:=1;
  for i:=c[1]+1 to c[1]+c[2] do b[i]:=2;
  for i:=c[1]+c[2]+1 to n do b[i]:=3;
  tot:=0;
  for i:=1 to n do
    for j:=1 to n do
      if (a[i]<>a[j]) and (a[i]=b[j]) and (a[j]=b[i]) then
        begin
          tmp:=a[i]; a[i]:=a[j]; a[j]:=tmp;
          inc(tot);
        end;
  tmp:=0;
  for i:=1 to n do
    if a[i]<>b[i] then inc(tmp);
  writeln(tot+tmp div 3*2);
  close(input); close(output);
end.
```

---

