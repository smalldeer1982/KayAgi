# 除法 Division

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=666

[PDF](https://uva.onlinejudge.org/external/7/p725.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/9177f6f6723402a8ca5cd51e53c7912c7289196b.png)

## 样例 #1

### 输入

```
61
62
0```

### 输出

```
There are no solutions for 61.

79546 / 01283 = 62
94736 / 01528 = 62```

# 题解

## 作者：huainan_marquis (赞：11)

这道题的整体思路跑不了，就是枚举abcde，然后再通过abcde/n得到fghij，但是看了一下现有的题解，在拆分这一步骤上太过繁琐，其实可以换一种思路，使用set非常轻易的实现。
```c
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;


int main()
{
    //freopen("a.txt","r",stdin);
    int n,cnt =0;
    while(~scanf("%d",&n)){
        if(n == 0) break;
        int cont =0;
        if(cnt++ != 0)cout<<endl;
        for(int i =12345;i<98765;i++){
            set<int>s1;
            if(i%n != 0) continue;
            int k = i/n;
            int j1 = i,j2 = i/n;
            if(j2<10000)s1.insert(0);
            while(j1 >0){
                s1.insert(j1%10);
                j1 /= 10;
            }
            while(j2 >0){
                s1.insert(j2%10);
                j2 /= 10;
            }
            if(s1.size() == 10){
                cont++;
                if(k<10000)
                    printf("%d / 0%d = %d\n",i,k,n);
                else
                    printf("%d / %d = %d\n",i,k,n);
            }
        }
        if(cont == 0)printf("There are no solutions for %d.\n",n);

    }
    return 0;
}

```
为了证明这个的正确性，给一个非数学性证明。首先abcde是从12345枚举到98765，
由五位组成，而n>=2&&n<=79,所以fghij一定是小于等于五位的，然后再加上一条如果f<10000那就insert（0），足够满足所有情况。

所以呀，其实做这种水题的时候也得想一下有没有更好的解题办法，而不是一味的背模板。

---

## 作者：ljcljc (赞：10)


**【算法分析】**

拿道题目第一眼，我就毫不犹豫的用了暴力枚举 。

我们可以先来枚举abcde，然后通过n推出fghij。

最后判断+输出 

**【AC代码】**
```cpp
#include<iostream> 
#include<cstring>
using namespace std;
int n,f[10]; 
int judge(int x,int y)
{
    memset(f,0,sizeof(f));//清0 
    int cnt=0;
    while(x!=0)
    {
        f[x%10]++;
        x/=10;
        cnt++;
    }
    if(cnt==4)//注意0! 
        f[0]++;
    while(y!=0)
    {
        f[y%10]++;
        y/=10;
    }
    for(int i=0;i<10;i++)//满足0~9都各有1个 
        if(f[i]!=1)
            return 0;
    return 1;
}
int main()
{
    int num=0;
    while(cin>>n&&n)
    {
        if(num++)
            cout<<"\n";
        int flag=0;
        //枚举abcde ￣△￣|| 
        for(int i=0;i<=9;i++)
            for(int j=0;j<=9;j++)
                for(int k=0;k<=9;k++)
                    for(int l=0;l<=9;l++)
                        for(int m=0;m<=9;m++)
                            if(judge(m+l*10+k*100+j*1000+i*10000,n*(m+l*10+k*100+j*1000+i*10000)))
                                cout<<n*(m+l*10+k*100+j*1000+i*10000)<<" / "<<i<<j<<k<<l<<m<<" = "<<n<<'\n',flag=1;//输出+标记 
        if(flag==0)//没找到 
            cout<<"There are no solutions for "<<n<<".\n";
    }
    return 0;
} 
```

---

## 作者：gcwixsxr (赞：7)

#### 本蒟蒻又来发题解了

这道题的思路:~~适用于各dalao的~~**深搜**

~~先吐槽一会儿UVA:~~

其实这道题最坑的是**输出格式!!!**

![](https://cdn.luogu.com.cn/upload/image_hosting/y5vqjbir.png)

看看样例:  两个输出**之间**有一个换行!!!幸好最后的输出有没有换行不重要;

~~不知道这道题的格式让多少人刷低了AC率~~


## 下面是代码区:

### 函数1:dfs

其实只用判断5位数即可,因为用这个五位数乘以n就可以算出另一个五位数,再判断数字有无重复;
```cpp
void dfs(int dep){//dep代表当前数字的位数
	if(dep==5){		//如果有5位了
		if(check()){//判断是否满足所有位数都不相同
			ans++;//ans加一,方便后面判断是否有解
			for(int i=0;i<=4;i++)
				printf("%d",sum2[i]);
			printf(" / ");
			for(int i=0;i<=4;i++)
				printf("%d",sum1[i]);
			printf(" = ");	
			printf("%d\n",n);//输出
		}
		memset(sum2,0,sizeof(sum2));
		memset(u,0,sizeof(u));//重置
		return ;
	}
	for(int i=0;i<=9;i++){
		if(vis[i])continue;
		vis[i]=1,sum1[dep]=i;
		dfs(dep+1);
		vis[i]=0,sum1[dep]=0;	//递归过程	
	}
}
```
### 函数2:check
判断有无重复的字符

```cpp
bool check(){
	for(int i=4;i>=0;i--){
		sum2[i]+=sum1[i]*n;//计算sum2的每一位
		if(i==0&&sum2[i]>=10){//如果sum2的最高位大于10
			return false;//返回不行
		}
		if(sum2[i]>=10)sum2[i-1]+=sum2[i]/10,sum2[i]%=10;//类似高精
		if(vis[sum2[i]]||u[sum2[i]])return false;
		u[sum2[i]]=true;//专门拿一个桶来判断sum2[i]是否用过,以免影响到dfs中的vis数组
	}
	return true;//返回可以
}
```

### AC代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,sum1[5],sum2[5],vis[10],u[10];
int n;
bool check(){
	for(int i=4;i>=0;i--){
		sum2[i]+=sum1[i]*n;
		if(i==0&&sum2[i]>=10){
			return false;
		}
		if(sum2[i]>=10)sum2[i-1]+=sum2[i]/10,sum2[i]%=10;
		if(vis[sum2[i]]||u[sum2[i]])return false;
		u[sum2[i]]=true;
	}
	return true;
}
void dfs(int dep){
	if(dep==5){		
		if(check()){
			ans++;
			for(int i=0;i<=4;i++)
				printf("%d",sum2[i]);
			printf(" / ");
			for(int i=0;i<=4;i++)
				printf("%d",sum1[i]);
			printf(" = ");	
			printf("%d\n",n);
		}
		memset(sum2,0,sizeof(sum2));
		memset(u,0,sizeof(u));
		return ;
	}
	for(int i=0;i<=9;i++){
		if(vis[i])continue;
		vis[i]=1,sum1[dep]=i;
		dfs(dep+1);
		vis[i]=0,sum1[dep]=0;		
	}
}
signed main(){
	scanf("%d",&n);	
	while(n){
		if(n<=80){
			ans=0;
			memset(vis,0,sizeof(vis));
			memset(sum1,0,sizeof(sum1));
			memset(sum2,0,sizeof(sum2));
			memset(u,0,sizeof(u));//疯狂重置
			dfs(0);
		}
		if(ans==0)printf("There are no solutions for %d.\n",n);	
		scanf("%d",&n);	
		if(n)cout<<endl;		
	}

	return 0;
}

```

---

## 作者：cyrxdzj (赞：1)

### 一、思路

如果用 DFS 枚举数字的每一位,一定会 TLE。

既然如此，我们可以枚举除数，再借助输入的商计算出被除数。然后，判断两个数字是否符合题意。

由于第二个数字是从低往高枚举的，并且输入的商也是正数，所以第一个数字也一定是从低往高的。

更多的解释可以查看代码注释。

### 二、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int input;
bool ans_flag;
bool prt_flag;
bool check(int num)//检查一个数。
{
	int tong[10];
	memset(tong,0,sizeof(tong));
	if(num<10000)//对于前导零。
	{
		tong[0]++;
	}
	while(num)
	{
		tong[num%10]++;
		if(tong[num%10]>=2)
		{
			return false;
		}
		num/=10;
	}
	if(tong[0]>=2)
	{
		return false;
	}
	return true;
}
bool check(int num1,int num2)//检查两个数。这里使用了函数重载。
{
	int tong[10];
	memset(tong,0,sizeof(tong));
	if(num1<10000)//对于前导零。
	{
		tong[0]++;
	}
	while(num1)
	{
		tong[num1%10]++;
		if(tong[num1%10]>=2)
		{
			return false;
		}
		num1/=10;
	}
	if(num2<10000)//对于前导零。
	{
		tong[0]++;
	}
	while(num2)
	{
		tong[num2%10]++;
		if(tong[num2%10]>=2)
		{
			return false;
		}
		num2/=10;
	}
	if(tong[0]>=2)
	{
		return false;
	}
	return true;
}
int main()
{
	while(scanf("%d",&input)&&input!=0)
	{
		if(prt_flag)//UVA毒瘤输出。
		{
			printf("\n");
		}
		else
		{
			prt_flag=true;
		}
		ans_flag=false;
		for(int num2=1234;num2<=98765;num2++)//枚举第二个数。第二个数最小是01234，最大是98765。
		{
			if(!check(num2))
			{
				continue;
			}
			int num1=num2*input;//通过除数和商计算被除数。
			if(num1>99999)//第一个数已经明显大于5位，此时再继续枚举是没有意义的，因此直接退出。
			{
				break;
			}
			if(check(num1,num2))
			{
				ans_flag=true;
				printf("%05d / %05d = %d\n",num1,num2,input);//有解输出。
			}
		}
		if(!ans_flag)
		{
			printf("There are no solutions for %d.\n",input);//无解输出。
		}
	}
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：YUKAYOUXIA (赞：1)

```cpp
#include<cstdio>
#include<cstring>
int n,ok,fi=0;
bool is[10];//标记0~9是否出现过
int t[5];
int w[5];

bool f(int x,int y){
	memset(is,0,sizeof(is));//清空
	for(int i=4;i>=0;--i){//分解数字
		t[i]=x%10;
		if(is[t[i]]){//如果0~9的某个数已出现过,就返回0
			return 0;
		}
		is[t[i]]=1;
		x/=10;
	}
	if(x!=0){//如果x的位数超过5,不能被分解干净,返回0
		return 0;
	}
	for(int i=4;i>=0;--i){//分解数字
		w[i]=y%10;
		if(is[w[i]]){//如果0~9的某个数已出现过,就返回0
			return 0;
		}
		is[w[i]]=1;
		y/=10;
	}
	if(y!=0){//如果y的位数超过5,不能被分解干净,返回0
		return 0;
	}
	return 1;
}

int main(){
	while(scanf("%d",&n)&&n){
		if(fi){//保证不输出多余空行
			printf("\n");
		}else{
			fi=1;
		}
		ok=1;//如果无解,ok为1
		for(int i=1234;i<=98765;++i){//枚举可能的被除数
			int y=i/n;
			if(y*n==i){//如果能相等
				if(f(i,y)){//分解并检验
					ok=0;//此时有解
					for(int i=0;i<5;++i){
						printf("%d",t[i]);
					}
					printf(" / ");
					for(int i=0;i<5;++i){
						printf("%d",w[i]);
					}
					printf(" = %d\n",n);
				}
			}
		}
		if(ok){//无解的打印
			printf("There are no solutions for %d.\n",n);
		}
	}


	return 0;
}
```


---

## 作者：PC_DOS (赞：1)

本题如果通过枚举10个数来做的话效率太低，我们可以改变思路：从1000到50000枚举分母并计算分子，接下来再验证是否包含了从0到9这10个数字。为了应对前导0的问题，我们可以在分母小于10000时直接标记0存在，因为根据输入数据可知分子必定小于分母。

此外，我们还可以再减轻一些工作量，由于根据输入数据可知分子必定小于分母，因此为了保证能涵盖10个数字，分子上无疑要大于10000且小于99999，而一旦出现第一个大于99999的分子，那么再增大分母就没有意义了，可以直接结束循环。

接下来还要注意格式的问题：输出完一组数据要换行。注意，如果不分青红皂白就直接加个输出换行符的语句会导致WA，因为多了一行空行。因此我们可以在输出一次询问的所有回应内容之前输出空行，但是还得处理一下第一个输出，因为第一个输出前也不需要换行。此外，输出可行答案的时候别忘了前导0的处理哦。

代码:
```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iDenominator, iNumerator, iAns; //iDenominator-分母；iNumerator-分子；iAns-商
	register int i, iTemp; //循环计数器和拆分数字时使用的临时量
	bool arrNums[10] = { 0 }; //标记0到9这10个数字是否存在的数组
	bool IsFound=false, IsNoOutput=true; //IsFound-找到答案；IsNoOutput-尚无输出
	while (cin >> iAns && iAns!=0){ //读入查询
		if (IsNoOutput) //如果还没有输出
			IsNoOutput = false; //标识为由输出
		else //如果先前已经有过输出
		    cout<<endl; //输出换行符
		for (iDenominator = 1000; iDenominator <= 50000; ++iDenominator){ //从1000到50000枚举分母
			iNumerator = iAns*iDenominator; //计算分子
			if (iNumerator > 99999){ //一旦出现第一个大于99999的分子，那么再增大分母就没有意义了，可以直接结束循环
			    break;
			}
			if (iNumerator < 10000){ //分子上无疑要大于10000，跳过下面的语句并继续枚举
			    continue;
			}
			if (iDenominator < 10000){ //为了应对前导0的问题，我们可以在分母小于10000时直接标记0存在
				arrNums[0] = true;
			}
			iTemp = iDenominator; //拆分分子
			while (iTemp != 0){
				arrNums[iTemp % 10] = true;
				iTemp /= 10;
			}
			iTemp = iNumerator; //拆分分母
			while (iTemp != 0){
				arrNums[iTemp % 10] = true;
				iTemp /= 10;
			}
			if (count(arrNums, arrNums + 10, false) == 0){ //如果数组中没有false，这里用了STL的count函数
				cout << iNumerator << " /" << (iDenominator < 10000 ? " 0" : " ") << iDenominator << " = " << iAns<<endl; //输出解，别忘了前导0的处理哦
				IsFound = true; //标识已找到
			}
			for (i = 0; i <= 9; ++i){ //初始化
				arrNums[i] = false;
			}
		}
		if (!IsFound){ //没找到
			cout << "There are no solutions for " << iAns << ".\n";
		}
		IsFound = false; //初始化
	}
	return 0; //结束
}
```

---

## 作者：algobase (赞：1)

这道题核心就是**暴力枚举**。

我们只需要枚举除数的每一种可能，并且计算出被除数，然后再判断被除数除以除数是否 $=n$，如果相等就输出。

**一个小优化：** 我们发现只有除数会有前导`0`，所以只用判断除数的位数是否是`4`位。如果是就把`0`也标记上。

代码我就不贴了，留给大家自己去思考。

------------
**Update：**
- $2020-05-18$ 发现多了一个逗号

---

## 作者：Reimilia (赞：1)

感觉好多人写的好麻烦啊，列举fghij后求出abcde后判断所有数字都不相同，最后在判断位数是4就在输出时多个0不就行了嘛= =

附上ac代码，很简单，~~看不懂怪我~~

```cpp
#include <iostream>
#include <cstring>

using namespace std;
int num[10], t;

void deal(int tmp)//分解数字并统计出现次数
{
	while (tmp)
	{
		t = tmp % 10;
		tmp /= 10;
		num[t]++;
	}
}

int digit(int n)//判断位数
{
	int i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return i;
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n)
	{
		int all;
		bool flag = false;
		for (int i = 1234; i < 49383; i++)
		{
			bool is = true;
			memset(num, 0, sizeof(num));
			all = i * n;
			if (all<98765)
			{
				deal(i); deal(all);
				for (int j = 1; j < 10; j++)
				{
					if (num[j] != 1)
					{
						is = false;
					}
				}
				if (is)
				{
					flag = true;
					int dit1 = digit(i);
					int dit2 = digit(all);
					if (dit1 == 4)
					{
						cout << all << " / 0" << i << " = " << n << endl;
					}
					else if (dit2 == 4)
					{
						cout << 0 << all << " / " << i << " = " << n << endl;
					}
					else
					{
						cout << all << " / " << i << " = " << n << endl;
					}
				}
			}
		}
		if (flag == false)
		{
			cout << "There is no solutions for " << n << "." << endl;
		}
		cout << endl;
	}
	return 0;
}
```


---

## 作者：Snowlanuck (赞：0)

这题最先的思路就是暴力枚举,但是如果双循环枚举估计会超时

那么就要降低复杂度,只用一遍循环计算出b的值就行了

不过这样需要拆数判断是否重复,有点复杂,我就想到了用深搜,不用拆数(但要合并!)

好吧,我也不知道我这是简单化问题还是复杂化,不过好歹也是一种新思路

参考代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

bool book[10], b[10]; int a[5];
int num; bool AKIOI = false;

void dfs(int step = 0)
{
	if (step == 5)
	{
		int numa = 0, numb = 0, t;
		for (int i = 0; i < 5; i++) { numa = numa * 10 + a[i]; } //从数组中计算numa的值
		t = numb = numa / num;
		if ((double)numa / (double)numb != num) { return; } //判断计算是否正确
		memset(b, 0, sizeof(b));
		if (numb < 10000 && numb >= 1000) { if (book[0]) { return; } b[0] = true; }
		while (t != 0)
		{//判断数字是否重复 b数组用来辅助判断
			if (book[t % 10] || b[t % 10]) { return; }
			b[t % 10] = true; t /= 10;
		}

		AKIOI = true;
		if ((numb < 10000 && numb >= 1000) || (numb > 10000)) { printf("%d / %05d = %d\n", numa, numb, num); }
		else AKIOI = false;
		return;
	}
	for (int i = 0; i <= 9; i++)
	{
		if (book[i]) { continue; }
		book[i] = true;
		a[step] = i; dfs(step + 1);
		book[i] = false;
	}
}

int main()
{
	int cnt = 0;
	while (cin >> num)
	{
		if (num == 0) { break; } AKIOI = false;
		if (cnt++) { cout << endl; }
		memset(book, 0, sizeof(book)); dfs();
		if (!AKIOI) { printf("There are no solutions for %d.\n", num); }
	}
	return 0;
}
```


---

## 作者：syf2008 (赞：0)

这题模拟就完事了
剪枝1：大过99999时不会出现abcde.

```
#include <bits/stdc++.h>
using namespace std;
int a,k,k1,k2,k3,k4,k5,flag,qwq;
int main()
{
	while(cin>>a&&a!=0)//多组输入
	{
		if(qwq)
		printf("\n");
		qwq=1;//UVA特性
		flag=0;//初始化
		for(int x1=0;x1<=9;x1++)
		for(int x2=0;x2<=9;x2++)
		for(int x3=0;x3<=9;x3++)
		for(int x4=0;x4<=9;x4++)
		for(int x5=0;x5<=9;x5++)//五位枚举
		{
        	if(x1==x2||x1==x3||x1==x4||x1==x5||x2==x3||x2==x4||x2==x5||x3==x4||x3==x5||x4==x5)
			continue;
		k=(x1*10000+x2*1000+x3*100+x4*10+x5)*a;
		if(k>=100000)
			break;//剪枝1
		k1=k/10000;
		k2=k/1000%10;
		k3=k/100%10;
		k4=k/10%10;
		k5=k%10;
		if(k1==k2||k1==k3||k1==k4||k1==k5||k2==k3||k2==k4||k2==k5||k3==k4||k3==k5||k4==k5)
			continue;
		if(k1==x1||k1==x2||k1==x3||k1==x4||k1==x5||k2==x1||k2==x2||k2==x3||k2==x4||k2==x5||k3==x1||k3==x2||k3==x3||k3==x4||k3==x5||k4==x1||k4==x2||k4==x3||k4==x4||k4==x5||k5==x1||k5==x2||k5==x3||k5==x4||k5==x5)
			continue;
		flag=1;//判断是否有满足条件的数
		cout<<k<<" / "<<x1<<x2<<x3<<x4<<x5<<" = "<<a<<endl;//当上面的条件均不成立，说明这个数可行，输出
		}
		if(!flag)//如果没有，输出
			printf("There are no solutions for %d.\n",a);
	}
}
```

---

