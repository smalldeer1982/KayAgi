# 生成元 Digit Generator

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4458

[PDF](https://uva.onlinejudge.org/external/15/p1583.pdf)

## 样例 #1

### 输入

```
3
216
121
2005```

### 输出

```
198
0
1979```

# 题解

## 作者：PC_DOS (赞：4)

不能读入一个数就算一个数，肯定TLE。

能不能再一开始从1枚举到100000，分别计算最小生成元存入数组呢？也不行，太慢了。

所以，应该从1枚举到100000，计算这些数所能生成的数并保存。也就是说，每枚举一个数，就计算它能够生成那个数，如果对应的数那没有生成元(由于从1开始枚举，因此可以保证第一个枚举道到的生成元一定最小)，那么就将这个数存入对应数的位置。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int arrAns[1000245]; //存放答案的数组，稍微大一点
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, i, j, iNum, iSum; //nCount-询问个数；i、j-循环计数器；iNum-询问的数字；iSum-累加器
	for (i = 1; i <= 100000; ++i){ //枚举生成元
		iSum = i; //记录累加器初值
		j = i; //复制一份
		while (j > 0){ //计算各位和
			iSum += j % 10;
			j /= 10;
		}
		if (arrAns[iSum] == 0){ //如果生成的数还没有生成元
			arrAns[iSum] = i; //记录生成元
		}
	}
	cin >> nCount; //读入询问个数
	for (i = 1; i <= nCount; ++i){ //接受询问
		cin >> iNum; //读入询问
		cout << arrAns[iNum] << endl; //输出答案，勿忘换行
	}
	return 0; //结束
}
```

---

## 作者：Clever_Jimmy (赞：2)

感觉可以发一波题解

很多大佬的题解里的ans数组都是从小到大枚举的

为什么不从大到小呢？还能省掉比较大小再赋值

```cpp
#include <cstdio>

int t,n,ans[100010];

int getsum(int number)//这个函数是求一个数的数位和的
{
	int sum=0;
	while(number)
	{
		sum+=number%10;
		number/=10;
	}
	return sum;
}

void init()//预处理
{
	for(int i=100000;i>=1;i--)//从后往前
	{
		int num=getsum(i);
		ans[num+i]=i;//这样能保证ans数组里的数一定是最小的，因为小的能把大的给覆盖掉
	}
}

int main()
{
	init();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
```

---

## 作者：HJY202three (赞：1)

[UVA1583生成元](https://www.luogu.com.cn/problem/UVA1583)


------------

# UVA1583 生成元 Digit Generator
先来说说思路。
## 思路
直接模拟1~x;如果test的数字和加上字己等于x，test就是x
的生成元。
## 代码
代码：
```cpp
#include<cstdio>
using namespace std;
int sum(int in)//数字和
{
    int ans=0;
    while(in!=0)
    {
        ans+=in%10;//拆位，把每一位加入ans
        in/=10;
    }
    return ans;
}
int main()
{
    int x;//shuru
    scanf("%d",&x);
    int ans=0;
    for(int i=1;i<=x;i++)
    {
        int test=i+sum(i);
        if(test==x)//对test实验，如果是x的生成元，ans就为x
        {
            ans=i;
            break;
        }
    }
    printf("%d",ans);//没有自然就是0
    return 0;//完美AC
}
```
(~~我不明白生成元除了做题有什么用么？~~)

~~求通过qwq（毕竟是本蒟蒻第一篇题解）~~

---

## 作者：竺子豪 (赞：0)


检查数据的时候，这个题是用的打表法，先把1-100000的结果存在数组里面，然后再查表即可。但是我一开始就输入了测试样例，然后在每个测试样例里面嵌套存表，忽然一想，这样如果数据大了，就是每重新一组数据都要打表算一次，这样如果有多组数据的话，肯定会TLE的，然后赶紧改了，就a了。。。。

这个题因为数组开得还是比较大的，如果放在main里面定义容易打开编辑框就直接退出，之前有过经验，所以定义了大数组，最好还是定义在外面。。。

还有这个题的需要注意的地方是if判断的那个位置，把相加得到的数作为数组元素的下标，因为要求的数是原数，小的那个，所以把原数作为数组元素存起来，然后判断下标和要求输入的数是否一样，一样的话就直接输出元素的值。。。

其实代码很简单，不过这种处理还是要想到。。。形成这种知道怎么处理问题的模式比较好。。。

上代码：
```cpp
#include <cmath>
#include <ctime>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#define INF (INT_MAX / 10)
#define clr(arr, val) memset(arr, val, sizeof(arr))
#define pb push_back
#define sz(a) ((int)(a).size())
 
using namespace std;
typedef set<int> si;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef long long ll;
 
const double esp = 1e-5;
 
#define N 100000+10
int a[N];  
int main()
{
	int i,T,n,sum;
	memset(a,0,sizeof(a));
	for(i=1;i<100000;i++)
	{
		sum=i;
		int m=i;
		while(m)
		{
			sum+=m%10;
			m/=10;
		}
		if(a[sum]==0||a[sum]>i)
		a[sum]=i;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%d\n",a[n]);
	}
	return 0;
}

```

---

## 作者：sss7020 (赞：0)

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int scy(int n){
    int j=n,ans=n;
    while(j){
        ans+=j%10;
        j/=10;
    }
    //取各个数位之和，再加n
    return ans;
}//写个函数简介一点
int a[1000000];
int main(){
    memset(a,0,sizeof(a));
    for(int i=1;i<=100000;i++){
        int k=scy(i);
        if(a[k]==0)a[k]=i;
    }//初始化
    int n,b[1000005];
    cin>>n;//
    for(int i=1;i<=n;i++){
        cin>>b[i];
        cout<<a[b[i]]<<endl;
    }//妙的地方来了：如果找不到的话，直接输出就是0（已经全部初始化）
    return 0;//完美结束
}

```

---

