# Triangle

## 题目描述

给定 $4$ 根木棍的长度，如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在 $3$ 根木棍可以组成退化的三角形(任意两边之和大于等于第三边，但是不是三角形)，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE``` 。

注意: 木棍不能折断，也不能只用一部分长度。

## 样例 #1

### 输入

```
4 2 1 3
```

### 输出

```
TRIANGLE
```

## 样例 #2

### 输入

```
7 2 2 4
```

### 输出

```
SEGMENT
```

## 样例 #3

### 输入

```
3 5 9 1
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：Heartlessly (赞：64)

## 算法介绍
- 据说这道题的正解是暴力枚举什么的，但是蒟蒻在这里给大家介绍另一种~~贪心的~~解法。
- 先把四根木棍的长度按从小到大排序。
- 从四根木棍中挑出三根显然只有 **4** 种方法（如下）

 1. **1 2 3**
 1. **1 2 4**
 1. **1 3 4**
 1. **2 3 4**

- 排列组合就是：$C_{4}^{3}= \frac{4!}{\left ( 4-3 \right )!3!}= \frac{4\times 3\times 2\times 1}{3\times 2\times 1}= 4$
- 其中有 **2** 种不需要考虑，原因如下：
- 如果**第一根木棍和第二根木棍的总长**大于**第四根**，那么就一定大于第三根，所以只要判断**第一根木棍和第二根木棍的总长**与**第三根**的关系。 
- 同理，如果**第一根木棍和第三根木棍的总长**大于**第四根**，那么**第二根木棍和第三根木棍的总长**也一定大于**第四根**，所以只要判断**第二根木棍和第三根木棍的总长**与**第四根**的关系。
- 也就是说，**2,3** 两种挑法可以忽略，退化的三角形也一样判断。
- 通过以上思路，并不难写出代码。
------------

## 示例代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int f[5];//数组存比较方便排序
int main(){
	for ( int i = 1; i <= 4; i++ )
	scanf ( "%d", &f[i] );
	sort ( f + 1, f + 5 );//快速排序
	if ( f[1] + f[2] > f[3] || f[2] + f[3] > f[4] ) printf ( "TRIANGLE\n" );
	else if ( f[1] + f[2] == f[3] || f[2] + f[3] == f[4] ) printf ( "SEGMENT\n" );
	else printf ( "IMPOSSIBLE\n" );
	return 0;
} 
```

---

## 作者：lemir3 (赞：22)

**一道不错的DFS入门题**

思路没什么好说的，直接解释代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5];
int u[4];
bool f[5],falg;
void dfs(int dep)
{
	if(dep==4)//因为dep是在为下一轮做准备，所以dep=3(准备选第3个数)时才选了2个数，所以要dep=4时来判断
	{
		if(u[1]+u[2]>u[3]&&u[1]+u[3]>u[2]&&u[2]+u[3]>u[1])
		{
			printf("TRIANGLE");//满足普通三角形，直接输出
			exit(0);//意为"正常退出程序"，相当于主函数里面的retrun 0,在DFS里面用可以节省搜到答案后回朔的时间
		}
		if(u[1]+u[2]>=u[3]&&u[1]+u[3]>=u[2]&&u[2]+u[3]>=u[1])falg=true;
 /*
 这里不能直接输出
 因为弱化三角形的优先级小于普通三角形，
 所以当木棍同时满足弱化三角形和普通三角形的条件时应该输出最优解普通三角形
 但因为用的是DFS，枚举数的顺序只和数据的顺序有关，于是满足弱化三角形时就直接输了,要到确认没有普通三角形时才能输
 (第一次竟然在在这里跪了QAQ)
 */
		return;
	}
	for(int i=1;i<=4;i++)
	if(f[i]==false)
	{
		f[i]=true;
		u[dep]=a[i];//把当前枚举到的组合临时存储下来
		dep++;//为下轮做准备
		dfs(dep);//刚学DFS时教练说内循环要写成镜像来回溯，于是我沿用到现在
		dep--;//撤销所有操作
		u[dep]=0;
		f[i]=false;
	}
}
int main()
{
	scanf("%d%d%d%d",a+1,a+2,a+3,a+4);//把数组当指针用，小绿书介绍过，也可以写scanf("%d%d%d%d",&a[1],&a[2],&a[3],&a[4])
	dfs(1);
	if(falg==true)printf("SEGMENT");//然而第2次又跪在打少了一个等号上(我太蒻了)
	else printf("IMPOSSIBLE");
return 0;
}
```

---

## 作者：RAYMOND_7 (赞：18)

# 此题为一道大水题~~~~
首先 , 数据范围就很小；
四个当中选三个；

时间复杂度O(4^3)

如果你会剪枝，
时间常数会很小

dfs后模拟一下即可

上代码

------------
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
void read(int &x){
	char c=getchar();
	int k=1;
	while(c<'0'||c>'9') {if(c=='-') k=-1;c=getchar();}
	for(x=0;c>='0'&&c<='9';c=getchar())
	x=x*10+c-'0';
	x*=k;
}
int n,u[5],a[7],ton[10];
bool b;
void dfs(int i){
	if(i>3){
		if(u[1]<u[2]+u[3]&&u[2]<u[1]+u[3]&&u[3]<u[1]+u[2]){
			b=true;n=1;
			return;
		}
		if(u[1]<=u[2]+u[3]&&u[2]<=u[1]+u[3]&&u[3]<=u[1]+u[2]){
			b=true;
			return;
		}
		return;
	}
	for(int j=1;j<=4;j++){
		if(ton[j]==0) {
			ton[j]=1;
			u[i]=a[j];
			dfs(i+1);
			u[i]=0;
			ton[j]=0;
		}
	}
}
int main(){
	cin>>a[1]>>a[2]>>a[3]>>a[4];
	dfs(1);
	if(b&&n) printf("TRIANGLE");
	else{
		if(b) printf("SEGMENT");
		else printf("IMPOSSIBLE");
	}
	return 0;
}


```
完美结束

看我这么辛苦点个赞吧

---

## 作者：球王武磊 (赞：12)

第一次发题解，希望大家支持。
这道题从4根木棍里选3根，直接枚举就可以AC，如先对4根木棍长度排序还可以减少需要考虑的情况。
为了解决一般问题，从更多的木棍里选出3根，就需要用递归来做。这道题若作为DFS题目适合新手练手，于是我用DFS来解决问题，下面是AC代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[4],b[3],flag=0;//a数组存所有木棍长度，b数组用来选取3根木棍
void dfs(int cur,int pla)//cur表示目前b数组已填数字的个数，pla表示前一个填的数在a数组中的位置 
{
	if(cur==3)
	{
		if(b[0]+b[1]>b[2])
			flag=2;
		if(b[0]+b[1]==b[2]&&!flag)
			flag=1;
	}//当b数组中填满3个数字时判断状态 
	else
	{
		for(int i=pla;i<4;i++)
		{
			b[cur]=a[i];
			dfs(cur+1,i+1);
		}
	}//没有满时继续往b数组中填数，满足后填数字比已填数字在a数组中位置靠后 
	return;
}//练习写dfs函数，以解决更具有普遍性的问题（木棍比4根更多时） 

int main()
{
	int i;
	for(i=0;i<4;i++)
		cin>>a[i];//a数组输入各木棍长度 
	sort(a,a+4);//将a数组从小到大排序，以便后续操作 
	dfs(0,0);
	if(flag==0) cout<<"IMPOSSIBLE";
	if(flag==1) cout<<"SEGMENT";
	if(flag==2) cout<<"TRIANGLE";//根据flag状态输出结果 
	return 0;
}
```


---

## 作者：singlewalker (赞：9)

# 由于只有四根木棍，选三根木棍用到三重循环复杂度并不高，想到可以枚举所有情况
## 判断的内容都来自于定义（三角形/退化的三角形）
## 将值存在数组而不是变量中更加方便，for循环即可写完所有情况
###  ~~此题较简单~~ 还是不要掉以轻心，注意三角形的判断优先！枚举判断完所有是否是三角形，再判断是否是退化的三角形
```
#include <bits/stdc++.h>//万能库最方便了
using namespace std;
   
int main()
{
    int a[5];
    ios::sync_with_stdio(0);     //关闭同步，一定程度上加速
    for(int i=1;i<=4;i++)
      cin>>a[i];//输入四个木棍长度到数组，方便读取
    for(int i=1;i<=4;i++)//三个循环暴力枚举可能挑选的三根木棍来判断
      for(int j=1;j<=4&&j!=i;j++)//注意木棍不能重复挑选：j！=i
        for(int p=1;p<=4&&p!=i&&p!=j;p++)
          {
				if(a[i]+a[j]>a[p]&&a[i]+a[p]>a[j]&&a[p]+a[j]>a[i]) {cout<<"TRIANGLE";return 0;}//是三角形要满足任意两边之和大于第三遍
		  }
	for(int i=1;i<=4;i++)
      for(int j=1;j<=4&&j!=i;j++)
        for(int p=1;p<=4&&p!=i&&p!=j;p++)
          {
				if(a[i]+a[j]>=a[p]&&a[i]+a[p]>=a[j]&&a[p]+a[j]>=a[i]) {cout<<"SEGMENT";return 0;}//这一个判断单列了一个循环，是因为三角形的判断优先，退化的三角形比三角形多条件
		  }
    cout<<"IMPOSSIBLE";  //两个循环中判断皆不满足，即不可能   
}
```

---

## 作者：封禁用户 (赞：3)

大家好，我这个蓝名小蒟蒻又双叒叕来写题解啦！

这题毫无疑问是很水的。但想要做这题，首先要知道一个~~幼儿园小班~~小学五年级的道理：三角形的两条短边相加必须大于第三边。

为什么呢？因为，如果两条短边相加等于第三边的话，就无法在两条边之间形成角度，否则就会有两条边够不着彼此，只能形成一条直线，也就是题目中所说的退化的三角形。如果小于的话就更不用说了，三条边互相碰不着。

解释了这么多，现在该开始讲正事儿了。

我们可以用3个for枚举三角形的三条边用哪条木棍，然后写一个函数，判断这三条边能不能构成三角形，或者是退化的三角形。

如下：
```c
	for(int i=1; i<=4; i++)
	{
		for(int j=1; j<=4; j++)
		{
			if(i==j)continue;
			for(int k=1; k<=4; k++)
			{
				if(k==i||k==j)continue;
				t=max(t,zajtc(a[i],a[k],a[j]));
			}
		}
	}
```
注意中间的continue不能省去，否则同一条木棍会被用多次，自然而然也就会“WA的一声哭了出来”。

zajtc函数如下：
```c
int zajtc(int x,int y,int z)
{
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	if(x+y==z)return 1;
	if(x+y>z)return 2;
	if(x+y<z)return 0;
}
```
如上文函数，我们先用前三句话把这三条枚举出来的边排好序，然后返回值，能组成三角形为2，能组成退化的三角形为1，啥都不能为0。

献完整AC程序：

```c
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>

using namespace std;
int zajtc(int x,int y,int z)
{
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	if(x+y==z)return 1;
	if(x+y>z)return 2;
	if(x+y<z)return 0;
}//上文提到过的函数部分
int a[5];
int t;
int main()
{
	cin>>a[1]>>a[2]>>a[3]>>a[4];
	for(int i=1; i<=4; i++)
	{
		for(int j=1; j<=4; j++)
		{
			if(i==j)continue;
			for(int k=1; k<=4; k++)
			{
				if(k==i||k==j)continue;
				t=max(t,zajtc(a[i],a[k],a[j]));
			}
		}
	}//上文的程序片段，for循环部分
	if(t==0)cout<<"IMPOSSIBLE";
	if(t==1)cout<<"SEGMENT";
	if(t==2)cout<<"TRIANGLE";//输出，上文提到过，0为不行，1为退化的三角形，2为三角形




    return 0;
}
```


---

## 作者：_Misaka_Mikoto (赞：3)

自定义面积函数
s>0,三角形
s==0,退化的三角形

```cpp
#include <iostream>
#include <cmath>
using namespace std;
double get_square(double a,double b,double c);
int main(){
    int i,j,k,m;
    cin>>i>>j>>k>>m;
    if(get_square(i,j,k)>0||get_square(i,j,m)>0||get_square(i,m,k)>0||get_square(j,m,k)>0){
        cout<<"TRIANGLE"; 
    }else if(get_square(i,j,k)==0||get_square(i,j,m)==0||get_square(i,m,k)==0||get_square(j,m,k)==0){
        cout<<"SEGMENT"; 
    }else{
        cout<<"IMPOSSIBLE"; 
    }
    return 0;
}

double get_square(double a,double b,double c){
    double p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));	
}
```

---

## 作者：PC_DOS (赞：3)

既然只有四根木棍，只需要暴力判一下能不能组成三角形/退化三角形就可以了。


假设4根木棍编号依次为0，1，2，3，那么有四种组合:


012

013

023

123

所以就可以暴力做了...

```cpp
#include <iostream>
using namespace std; //头文件和命名空间
bool isTriangle(int iLength1, int iLength2, int iLength3){ 
    return (iLength1 + iLength2 > iLength3 && iLength1 + iLength3 > iLength2 && iLength3 + iLength2 > iLength1);
} //判断能不能构成三角形: 任意两边之和大于第三边
bool isSegment(int iLength1, int iLength2, int iLength3){
    return (iLength1 + iLength2 >= iLength3 && iLength1 + iLength3 >= iLength2 && iLength3 + iLength2 >= iLength1);
} //判断能不能构成退化三角形: 任意两边之和大于等于第三边
int main(){
    ios::sync_with_stdio(false); //关闭同步，一定意义上的输入输出加速。
    int arrSticks[4]; //开一个由四个元素组成的数组，记录木棍的长度
    cin >> arrSticks[0] >> arrSticks[1] >> arrSticks[2] >> arrSticks[3]; //输入4根木棍的长度
    if (isTriangle(arrSticks[0], arrSticks[1], arrSticks[2]) || isTriangle(arrSticks[0], arrSticks[1], arrSticks[3]) || isTriangle(arrSticks[1], arrSticks[2], arrSticks[3]) || isTriangle(arrSticks[0], arrSticks[2], arrSticks[3])) //如果可以组成三角形
        cout << "TRIANGLE";
    else if (isSegment(arrSticks[0], arrSticks[1], arrSticks[2]) || isSegment(arrSticks[0], arrSticks[1], arrSticks[3]) || isSegment(arrSticks[1], arrSticks[2], arrSticks[3]) || isSegment(arrSticks[0], arrSticks[2], arrSticks[3])) //如果可以组成退化三角形
        cout << "SEGMENT";
    else //都不行QwQ
        cout << "IMPOSSIBLE";
    return 0; //结束
}
```

---

## 作者：Cambridge (赞：2)


小学生又来发题解了！

这道题很简单。如果读者们不知道如何判断三角形，本蒟蒻就在这说一下：如果任意两个边加起来的和都大于第三条边，那它就是一个三角形。如果还不懂，请读者自行在草稿纸上画一下，本蒟蒻在此不再论述。了解完性质后，我们直接讲解法：我们不需深搜、不需排列组合、更不需排序，我们只需枚举暴力。读入不多讲，先判断它是不是标准三角形，如果是，输出"TRIANGLE"，退出程序。如果不是，再判断它是不是退化三角形。如果是，输出"SEGMENT"，退出程序。如果都不是，输出"IMPOSSIBLE"。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int a[5];
    int main()
    {
    for(int i=1; i<=4; i++)
    {
        cin>>a[i];//读入
    }
    for(int i=1; i<=4; i++)//枚举
        for(int j=1; j<=4; j++)
            if(i!=j)//优化
                for(int k=1; k<=4; k++)
                    if(k!=j&&k!=i)
                        if(a[i]+a[j]>a[k]&&a[i]+a[k]>a[j]&&a[j]+a[k]>a[i])
                        {
                            cout<<"TRIANGLE";
                            return 0;
                        }
    for(int i=1; i<=4; i++)//枚举
        for(int j=1; j<=4; j++)
            if(i!=j)//优化
                for(int k=1; k<=4; k++)
                    if(k!=j&&k!=i)
                        if(a[i]+a[j]>=a[k]&&a[i]+a[k]>=a[j]&&a[j]+a[k]>=a[i])
                        {
                            cout<<"SEGMENT";
                            return 0;
                        }//自己看题
    cout<<"IMPOSSIBLE";//如果都不是，输出
    return 0;//退出程序
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：Siyuan (赞：2)

来一个排序思想的题解！


本题思路：


1. 先将4条边进行排序。


2. 根据三角形判定公式的推导公式：最长边<其余两边，进行判定和输出（**TRIANGLE**）。


3. 如果是**SEGMENT**，则最长边==其余两边。


4. 不然则为**IMPOSSIBLE**。


上代码！


```cpp
#include<iostream>
using namespace std;
int a[5];
inline void change(int &a,int &b)
    {int t=a;a=b;b=t;}
int main()
{
    ios::sync_with_stdio(0);     //关闭同步
    for(int i=1;i<=4;i++)  cin>>a[i];
    for(int i=1;i<=3;i++)     //冒泡排序……
        for(int j=i+1;j<=4;j++)
            if(a[i]>a[j])  change(a[i],a[j]);
    if(a[3]<a[1]+a[2]||a[4]<a[1]+a[2]||a[4]<a[1]+a[3]||a[4]<a[2]+a[3])     //TRIANGLE
        {cout<<"TRIANGLE";return 0;}
    if(a[3]==a[1]+a[2]||a[4]==a[1]+a[2]||a[4]==a[1]+a[3]||a[4]==a[2]+a[3])     //SEGMENT
        {cout<<"SEGMENT";return 0;}
    cout<<"IMPOSSIBLE";
    return 0;
}
```

---

## 作者：Porsche (赞：2)

A了之后闲着无事看了看第一篇题解，结果就发现了问题，他的思路真的很棒，但是不够严谨。

他的思路认为只要两个边之和大于第三边就能组成三角形了，这总思路是不严谨的，我们还应该满足两边之差小于第三边，他没有进行这一步判断，还好数据比较水，否则他就凉凉了。

当然不止这个地方需要进行修改，还要考虑输出“SEGMENT”的情况，这时候就不是想那位大佬一样只需要判断两个边的和等于第三个边了，还要考虑两个边的差大于第三边的情况。

输出“IMPOSSIBLE”的情况没有变化，还是两边之和小于第三边。

谨以此题解提醒那些理解错题意的神犇们，数据过水，理解错题意也能过，贴上我的代码，仅供大佬们参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[5];
	for(int i=1;i<=4;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+5);//排序方便枚举
	if(((a[1]+a[2])>a[3])&&(abs(a[1]-a[2])<a[3])||((a[2]+a[3])>a[4])&&(abs(a[2]-a[3])<a[4]))printf("TRIANGLE");//判断是否是一个三角形（两边之和大于第三边，两边之差还要小于第三遍！！！）
	else if((a[1]+a[2])>=a[3]||(a[2]+a[3])>=a[4])printf("SEGMENT");//判断是否是一个退化的三角形（不仅有两边之和等于第三边的情况，还要有两边之差大于第三遍的情况！！！）
	else printf("IMPOSSIBLE");//其他情况没有更正 
	return 0;
}
```

---

## 作者：wubaiting2020 (赞：0)

这道题就只需暴力枚举即可，~~结果被我做成了像Floyd一样……~~上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a[5];
    for(int i=1;i<=4;i++)cin>>a[i];
    for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
    for(int k=1;k<=4;k++)
    if(i!=j&&j!=k&&k!=i&&a[i]+a[j]>a[k]&&a[i]+a[k]>a[j]&&a[k]+a[j]>a[i]){puts("TRIANGLE");return 0;}
    //三重循环，先判断是否是同一条边，再按三角形性质判断
    for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
    for(int k=1;k<=4;k++)
    if(i!=j&&j!=k&&k!=i&&a[i]+a[j]>=a[k]&&a[i]+a[k]>=a[j]&&a[k]+a[j]>=a[i]){puts("SEGMENT");return 0;}
    //同理，因为上面没退，所以不是三角形，只需判断是不是退化的即可
    puts("IMPOSSIBLE");
    //不是三角形也不是退化三角形就输出
    return 0;
}
```


---

## 作者：Minecraft_slime (赞：0)

暴力判断就行了

判断可不可以组成三角形

不行的话在判断可不可以组成退化三角形

还是不行的话就输出“IMPOSSIBLE”就OK了

上代码！：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
long long a,b,c,d;//定义题目中说的4个数 
int main()
{
    cin>>a>>b>>c>>d; //输入 
    if(a+b>c && a+c>b && b+c>a) //判断4个数中是不是有3根小棒可以组成三角形 
    cout<<"TRIANGLE"; 
    else if(a+b>d && a+d>b && b+d>a) //要记住，任意两边之和大于第三边，就是三角形 
    cout<<"TRIANGLE"; 
    else if(c+b>d && c+d>b && b+d>c) 
    cout<<"TRIANGLE"; 
    else if(a+c>d && a+d>c && c+d>a) 
    cout<<"TRIANGLE"; 
    else if(a+b>=c && a+c>=b && b+c>=a) //判断4个数中是不是有3根小棒可以组成退化三角形 
    cout<<"SEGMENT"; 
    else if(a+b>=d && a+d>=b && b+d>=a) //要记住，任意两边之和等于第三边，就是退化三角形
    cout<<"SEGMENT"; 
    else if(c+b>=d && c+d>=b && b+d>=c) 
    cout<<"SEGMENT"; 
    else if(a+c>=d && a+d>=c && c+d>=a) 
    cout<<"SEGMENT"; 
	else cout<<"IMPOSSIBLE";   //否则输出"IMPOSSIBLE"，因为不能组成三角形和退化三角形 
	
    return 0;//这不用我说吧 。。。 
    
}

```

---

