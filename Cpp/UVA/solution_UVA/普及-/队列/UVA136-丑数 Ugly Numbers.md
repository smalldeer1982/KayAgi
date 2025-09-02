# 丑数 Ugly Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=72

[PDF](https://uva.onlinejudge.org/external/1/p136.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/9235847457e3c8f707f609605cbc21fd7bb05029.png)

## 样例 #1

### 输入

```
```

### 输出

```
The 1500'th ugly number is &lt;number&gt;.```

# 题解

## 作者：PC_DOS (赞：37)

~~WA这个题居然没有输入，那当然是写个暴搜放在那里跑然后打表啊。~~

```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
    cout<<"The 1500'th ugly number is 859963392.\n"; //别忘了换行
    return 0; //结束
}
```

附上暴搜~~TLE~~源码:
```
#include <iostream>
using namespace std; //头文件和命名空间
bool IsUglyNum(long long iNum){ //判断是不是丑数
	while (iNum >= 2){ //逐层除以2，3，5
		if (iNum % 2 == 0)
			iNum /= 2;
		else if (iNum % 3 == 0) 
			iNum /= 3;
		else if (iNum % 5 == 0) 
			iNum /= 5;
		else //如果这个数大于等于2，但是2，3，5不是其因子
			return false; //肯定不是
	}
	return iNum == 1; //判断最后是不是1，如果是拿这个数就是丑数
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long iNum=2, nCount = 1; //枚举的数字和已经得到的丑数的个数
	while (1){
		if (IsUglyNum(iNum)){ //如果是丑数
			++nCount; //个数加一
		}
		if (nCount == 1500){ //如果找到第1500个丑数了
			cout << iNum << endl; //输出
			break; //跳出循环
		}
		++iNum; //继续枚举
	}
	return 0; //结束
}
```

---

## 作者：Apostata (赞：15)

看了楼上的代码，我觉得可以简单一点......
~~我省了两行......

```cpp
#include<iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int a[1500 + 5] = {1},t2 = 0,t3 = 0,t5 = 0;
	for(int i = 1;i <= 1500;i ++)
	{
		if(a[t2] * 2 == a[i - 1])
			t2 ++;
		if(a[t3] * 3 == a[i - 1])
			t3 ++;
		if(a[t5] * 5 == a[i - 1])
			t5 ++;
		a[i] = min(min(a[t2] * 2,a[t3] * 3),a[t5] * 5);
	}
	cout << "The 1500'th ugly number is " << a[1499] << "." <<"\n";
	return 0;
}
```
第一次交题解，求过

---

## 作者：ct2019 (赞：13)

注意这题输出不带尖括号,要带句号!!~~WA了2次~~

丑数的素因子都是**2,3,5**，我们不妨称它们为“**丑因子**”。由丑数性质可得，**一个丑数必然可以由另一个丑数和丑因子(或1)相乘得到**。

因此我们可以从2,3,5这些最小的丑数开始，分别乘以自身的丑因子递增，然后从乘得的结果中选一个最小的记录下来。这样一次操作就得到一个新的丑数。最后答案输出第1500个丑数~~就可以了~~。

AC代码：
```c
#include<stdio.h>
#define N 1500

int s[N]={1};

int min(int a, int b, int c)
{
    if(a<b)return a<c?a:c;
    else return b<c?b:c;
}

void init()
{
    int f2=2,f3=3,f5=5,i2=0,i3=0,i5=0;
    int i=1;
    while(i<N)
    {
        s[i] = min(f2,f3,f5);
        if(s[i]==f2)
            f2 = s[++i2]*2;
        if(s[i]==f3)
            f3 = s[++i3]*3;
        if(s[i]==f5)
            f5=s[++i5]*5;
        i++;
    }
}

int main()
{
    init();
    printf("The 1500'th ugly number is %lld.\n",s[1500-1]);
    return 0;
}

```


---

## 作者：adding_milk (赞：8)

这道题有点BFS的思想，就是一个一个扩展，最后找到1500个即可。这里的代码比较简短，思想是**单序列三下标**。
```
#include <cstdio>
using namespace std;
int p2=1,p3=1,p5=1,a[1505]={0,1},x;
int min3(int a,int b,int c){//三者取最小值，等于min(min(a,b),c),但我喜欢自定义函数 
	if (a<=b)
	  if (a<=c)
	    return a;
	  else
	    return c;
   else if (b<=c) 
          return b;
        else  return c;	    
}
int main(){
	for (int i=2;i<=1500;i++){
		x=min3(2*a[p2],3*a[p3],5*a[p5]);//当前三个选项的最小值 
		a[i]=x;//扩展 
		if (x==2*a[p2])  p2++;//以下3行避免重复出现一个数（就是去重） 
		if (x==3*a[p3])  p3++;
		if (x==5*a[p5])  p5++;
//这里下标不断++，是为了遍历到所有的点*2,*3,*5的值 
	}
	printf("The 1500'th ugly number is %d.\n",a[1500]);//输出 
	return 0;
}
```
主程序真的很短，去掉函数也就十几行。详解在注释里，当然，这个程序老师讲过~~（我还是调了好几遍）~~，离不开老师的帮助。

---

## 作者：233333loog (赞：8)

```cpp
   使用优先队列解决即可。
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int coeff[3]={2,3,5};
int main()
{
    priority_queue<ll,vector<ll>,greater<ll> > pq;// 优先队列
    set<ll> s;
    pq.push(1);
    s.insert(1);
    for(int i=1;;i++){
        ll x=pq.top();pq.pop();
        if(i==1500){
            cout<<"The 1500'th ugly number is "<<x<<'.'<<endl;
            break;
        }
        for(int j=0;j<3;j++){
            ll x2=x*coeff[j];
            if(!s.count(x2)){
                s.insert(x2);pq.push(x2);
            }
        }
    }
}

```

---

## 作者：血色黄昏 (赞：6)

用python自己手写了个小根堆...~~感觉自己很sb~~

感觉这道题用堆很好做啊，每次弹出堆顶（最小）元素，把他的*2，*3，*5全部扔进堆并且排序，这样就能用O（1）时间查找了

~~当然这道题只用输出第1500个直接暴力也是可以的~~

附上找丑数的代码（堆的函数我自己写的，每个函数的作用都已标记，具体怎么实现的就自己百度吧）
```python
class MinHeap(object):#最小堆
    def __init__(self):
        super(MinHeap, self).__init__()
        self.data = []#初始化

    def add(self, a):#加进一个元素
        self.data.append(a)
        i = len(self.data) - 1
        parent = (i - 1) // 2
        while i > 0 and self.data[i] < self.data[parent]:
            t = self.data[i]
            self.data[i] = self.data[parent]
            self.data[parent] = t
            i = parent
            parent = (i - 1) // 2

    def adjust_max_heap(self, i):#堆里面排个序
        max_index = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < len(self.data) and self.data[i] > self.data[left]:
            max_index = left

        if right < len(self.data) and self.data[max_index] > self.data[right]:
            max_index = right

        if max_index != i:
            t = self.data[i]
            self.data[i] = self.data[max_index]
            self.data[max_index] = t
            self.adjust_max_heap(max_index)

    def pop(self):#弹出堆顶元素
        if len(self.data) == 0:
            return None
        if len(self.data) == 1:
            return self.data.pop()

        t = self.data[0]
        self.data[0] = self.data[-1]
        self.data.pop()
        self.adjust_max_heap(0)

        return t

    def empty(self):#判空
        return len(self.data) == 0

#主程序来啦
Hash = {1}#用了个hash
num = []#储存答案
l = MinHeap()#建立对象
l.add(1)#先把1加进去
for i in range(1500):#找1500个
    Q = l.pop()#Q变为堆顶元素
    num.append(Q)#把这个丑数加进去
    for i in [2, 3, 5]:
        ans = Q * i#分别*235
        if ans not in Hash:#如果不在Hash里
            Hash.add(ans)#Hash里加上，代表搜过
            l.add(ans)#加进堆里
print(num[1499)#输出第1500个
```

输出为859963392

所以直接写个
```python
print("The 1500'th ugly number is 859963392.")
```
交上去就完事了

说句闲话：怎么就我一个用python和堆做的....



---

## 作者：WanderingTrader (赞：4)

数学题，打表自然是最好的方法。  
### 题目分析
我们发现，根据“丑数”的特征，只要$n$是丑数，$2n,3n,5n$必然都是丑数。  
这样我们可以进行类似BFS的操作了。  
### 打表生成器
首先一个优先队列：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000000005
bool vis[N];
#define ll long long
priority_queue <ll,vector<ll>,greater<ll> > pq;
int main(){
	ll cnt = 0,k;
	pq.push(1);
	return 0;
}
```
只要$cnt<1500$，我们就不停的做如下操作：
```cpp
while(cnt < 1500)
{
	k = pq.top();
	pq.pop();
	if(vis[k]) continue;
	vis[k] = 1;
	cnt ++;
	pq.push(2*k);
	pq.push(3*k);
	pq.push(5*k);
}
```
是不是非常眼熟？  
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000000005
bool vis[N];
#define ll long long
priority_queue <ll,vector<ll>,greater<ll> > pq;
int main(){
	ll cnt = 0,k;
	pq.push(1);
	while(cnt <= 1500)
	{
		k = pq.top();
		pq.pop();
		if(vis[k]) continue;
		vis[k] = 1;
		cnt ++;
		printf("%lld %lld\n",cnt,k);
		pq.push(2*k);
		pq.push(3*k);
		pq.push(5*k);
	}
	printf("%lld\n",k);
	return 0;
}
```
得到结果：
```
859963392
```
### 正式代码
既然得到结果了，那么：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	printf("The 1500'th ugly number is 859963392.\n");
	return 0;
}
```
解决问题！  
别忘了换行！别忘了换行！别忘了换行！重要的事说三遍！  
笔者的UVA“坏了”，所以只好去官网上提交，$AC$。  
$\mathrm{The\ end.}$

---

## 作者：hero_brine (赞：3)

本蒟蒻在此水一篇Java代码，AC代码如下：
```java
public class Main{
	public static void main(String[] args){
		System.out.println("The 1500'th ugly number is 859963392.");
	}
}
```
至于答案是如何得出的，请看下面的~~十分钟~~代码：
```java
public class Main//一定要写成Main
{
    static long num,count;//记得使用static
    public static boolean ugly(long num){
        boolean flag=true;//定义标志
        if (num==1) return false;//特判
        while (num>=2){
            if (num%2==0)   num/=2;
            if (num%3==0)   num/=3;
            if (num%5==0)   num/=5;
            else    flag=false;
        }
        return flag;
    }
    public static void main(final String[] args){//final是VSC自动加上去的
        num = 1;count = 0;//从1开始判断
        while (true){
            if (ugly(num))  count++;//计数器++
            if (count==1500){
                System.out.println(num);break;//输出加退出循环
            }
        }
        num++;
    }
}
```
PS:注意事项均在代码的注释里面

---

