# Almost Prime

## 题目描述

一个数如果恰好有两个不同质因子，那它被叫做几乎是质数的数。例如：`6,18,24`就是几乎是质数的数，而`4,8,9,42`不是，请你找出 $1$ 到 $n$ 中几乎是质数的数有多少个。

## 样例 #1

### 输入

```
10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
21
```

### 输出

```
8
```

# 题解

## 作者：旋风猪皮 (赞：8)

我们要找恰好有两个质因数的数，因此我们要先把一个数所有的因数找出来，
然后再判断这些书里面有几个是质数。
但如果这样做应该是会超时的（我没仔细算过，但是我不是这样做的），我们可以换一种方法，用线性筛素数来找素数。我们可以开一个数组b，b[i]代表i有几个质因数。当我们发现一个数是素数时，我们就把n以内是这个数倍数的k找出来，然后b[k]++。到最后，我们再枚举1到n，b[i]如果为2，那么就把总数+1，输出总数，就是最后的答案。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,b[3001]={0},s=0;//b的用处如上，s为1到n里面的“几乎质数”
int main()
{
	b[1]=1;//1不是质数，特判一下，
	cin>>n;
	for(int i=2;i<=n;i++)//筛素数
    //注意筛数范围，由于要找出一个数的所有质因数，所以必须枚举到n
    //而不是sqrt（n）
	if(b[i]==0)//我们用0表示这个数为质数，这里代表发现一个质数
	{
		for(int j=2;j*i<=n;j++)//把这个数的倍数都枚举一遍
		b[i*j]++;//i的倍数都加一个质因数
        //注意这里，我们在加质因数的时候，也正好把不是质数的数排除了
        //因为b[i*j]都+了1，因此他们都不是0了，所以不是质数了
	}
	for(int i=1;i<=n;i++)
	if(b[i]==2) s++;//枚举一遍，看那些数正好有两个质因数
	cout<<s;//输出总数
	return 0;
}
```

---

## 作者：Chthology (赞：2)

思路很简单啊。。从6开始到n枚举（1到5最多只有一个质因数），判断每一个数是否有两个

虽然这题能~~毫无艺术性的~~不带任何优化在线判素数$O(n^2\sqrt{n})$水过，然而如果数据稍微大一点QwQ线性筛+优化会好一点。

---

优化：

ⅰ~~线性筛就不讲了吧~~有线性筛就不用在线做了，时间复杂度为$O(n)$

具体实现：
```
int temp[500];//这个要开大点，一开始开400卡了半天

void prime(){
	p[0]=true,p[1]=true;
	int cnt=1;
	for(register int i=1;i<=n;++i){
		if(!p[i]) temp[cnt++]=i;
		for(register int j=1;j<cnt&&temp[j]*i<=n;++j) p[temp[j]*i]=true;
	}
}
```

ⅱ在判断时，完全可以把原来的$O(n)$优化到$O(\sqrt{n})$

当发现一个可以整除当前数的数时，如果是素数，则质因数个数+1，如果**_当前数除以该数的值和该数不同_**,且当前数除以该数的值为素数，则质因数个数也+1，如果质因数个数>2则直接返回false

具体实现：
```
bool check(int x){
	int t=0;
	for(register int i=2;i<=sqrt(x);++i){
		if(x%i==0&&!p[i]) ++t;
		if(x%i==0&&x/i!=i&&!p[x/i]) ++t;
		if(t>2) break;//剪枝
	}
	//cout<<x<<' '<<t<<endl;
	if(t==2) return true;
	else return false;
}
```
经优化，时间复杂度便~~完美~~的从$O(n^2\sqrt{n})$变成了$O(n\sqrt{n})$

---

完整代码:
```
#include<bits/stdc++.h>
using namespace std;

int n,temp[500];
bool p[3005];

//线性筛
void prime(){
	p[0]=true,p[1]=true;
	int cnt=1;
	for(register int i=1;i<=n;++i){
		if(!p[i]) temp[cnt++]=i;
		for(register int j=1;j<cnt&&temp[j]*i<=n;++j) p[temp[j]*i]=true;
	}
}

//判断函数
bool check(int x){
	int t=0;
	for(register int i=2;i<=sqrt(x);++i){
		if(x%i==0&&!p[i]) ++t;
		if(x%i==0&&x/i!=i&&!p[x/i]) ++t;
		if(t>2) break;
	}
	//cout<<x<<' '<<t<<endl;
	if(t==2) return true;
	else return false;
}

int main(){
	cin>>n;
	prime();
	int ans=0;
	for(register int i=6;i<=n;++i) if(check(i)) ++ans;
	cout<<ans;
}
```

---

## 作者：PC_DOS (赞：2)

其实直接从1枚举到结束，对每一个数枚举因数，然后判断这些数里面有几个是质数也是可以的。

但是请注意：不要给计数器赋初值1之后从6开始枚举，最好直接从1或者2开始。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
bool IsPrime(long long iNum){ //判断是不是素数的函数
	register long long i;
	if (iNum <= 1)
		return false;
	for (i = 2; i <= sqrt(iNum); ++i){
		if (iNum%i == 0){
			return false;
		}
	}
	return true;
}
long long GetPrimeFactorCount(long long iNum){ //获取一个数的素因数个数
	register long long i;
	long long nCount = 0;
	for (i = 2; i <= iNum; ++i){
		if (iNum%i == 0){
			if (IsPrime(i)){
				++nCount;
			}
		}
	}
	return nCount;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	register int i; //循环计数器
	int nCount=0, iEnd; //nCount-计数器；iEnd-终止数
	cin >> iEnd; //输入终止数
	for (i = 2; i <= iEnd; ++i){ //枚举
		if (GetPrimeFactorCount(i) == 2){ //如果恰好有两个质因数
			++nCount; //计数器加一
		}
	}
	cout << nCount; //输出答案
	return 0; //结束
}
```

GetPrimeFactorCount这个函数做了很多无用的计算(当已经找到2个质因数时，如果再找到一个，必然不是"类素数")，可以适当加以改造，将其改为布尔型函数IsAlmostPrime，当质因数计数器大于2时直接返回false以减少判断素数的次数:
```
bool IsAlmostPrime(long long iNum){
	register long long i;
	long long nCount = 0;
	for (i = 2; i <= iNum; ++i){
		if (iNum%i == 0){
			if (IsPrime(i)){
				++nCount;
			}
			if (nCount > 2){
				return false;
			}
		}
	}
	return nCount==2;
}
```

---

## 作者：CJHGOD (赞：1)

蒟蒻题解代码有点长，请巨佬们见谅

我的思路是：

1.  判素数（那个数是不是质因子）

1.  找约数（有点长，后面会解释，特判比较多）

1.  如果质因子是2，s++

## 所以接下来我要告诉你们找约数的过程（看下面）

```cpp
int fin(int x){
	int s=0;
	for(int i=2;i*i<=x;i++){
		if(x%i!=0)continue;
		if(pr(i)&&i!=x/i)s++;
		if(pr(x/i)&&i!=x/i)s++;
		if(i*i==x&&pr(i))s++;
	}
	return s;
}

```
第一个if，如果不是x的约数，直接continue掉

第二个if，判x；同样第三个判x/i；

第四个if，如果是平方数（比如16）的特判

i！=x/i的原因是去重，方便类似36,144等数的查找

# （不还是平方数么）

接下来推出完整代码

```cpp
#pragma GCC optimize(3)//O3好习惯
#include<bits/stdc++.h>//万能头文件
using namespace std;
bool pr(int x){
	if(x<2)return 0;
	for(int i=2;i*i<=x;i++){
		if(x%i==0)return 0;
	}
	return 1;
}//判素数，这没什么好讲的
int fin(int x){
	int s=0;
	for(int i=2;i*i<=x;i++){
		if(x%i!=0)continue;
		if(pr(i)&&i!=x/i)s++;
		if(pr(x/i)&&i!=x/i)s++;
		if(i*i==x&&pr(i))s++;
	}
	return s;
}//刚才已经讲过了，不予解释
int main(){
	ios::sync_with_stdio(0);//输入输出流优化
	int n;
	cin>>n;
	int s=0;
	for(int i=1;i<=n;i++){
		if(fin(i)==2){//两个质因子
			s++;
		}//如果几乎是素数，s++
	}
	cout<<s;
    return 0;//finish the program
}

```


---

