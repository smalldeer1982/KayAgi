# [GCJ 2017 #1A] Alphabet Cake

## 题目描述

你正在为一些孩子举办一个聚会，并为他们准备了一个蛋糕，蛋糕的形状是一个 $R$ 行 $C$ 列的网格。你的助手已经开始装饰蛋糕，在每个孩子的首字母上用糖霜写在蛋糕的某一个格子里。每个格子最多只包含一个首字母，并且没有两个孩子的首字母相同，因此每个首字母在蛋糕上只出现一次。

每个孩子都希望得到一块包含自己首字母且不包含其他孩子首字母的矩形（与网格对齐）蛋糕。你能否为蛋糕上的每一个空白格子分配归属，使得每个孩子都能得到满足要求的蛋糕块？保证一定存在可行解。蛋糕不需要平均分配，甚至有的孩子可能只得到 $1 \times 1$ 的小块；这将是关于不公平的宝贵人生课程。

## 说明/提示

**样例解释**

样例输出展示了样例数据的一组可行解。其他解也是可能的。

**数据范围**

- $1 \leq T \leq 100$。
- 输入网格中至少有一个字母。
- 每个字母最多只在一个格子中出现一次。
- 保证每组测试数据都至少有一个解。

**小数据范围（8 分，测试点 1 - 可见）**

- $1 \leq R \leq 12$。
- $1 \leq C \leq 12$。
- $R \times C \leq 12$。

**大数据范围（13 分，测试点 2 - 隐藏）**

- $1 \leq R \leq 25$。
- $1 \leq C \leq 25$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 3
G??
?C?
??J
3 4
CODE
????
?JAM
2 2
CA
KE```

### 输出

```
Case #1:
GGJ
CCJ
CCJ
Case #2:
CODE
COAE
JJAM
Case #3:
CA
KE```

# 题解

## 作者：llh2012 (赞：2)

# 题意
给定一个 $R$ 行 $C$ 列的网格，上有一些字母，要求一个将已有字母填充至无字母处，使所有由相同字母组成的图形均为矩形的填充方法。
# 思路
~~看到标签~~想到贪心。
### 贪心方法
在每一行中，一定能将其划分为多个不同字母组成的矩形，所以将每一行都分开处理再合并。若这一行输入的全部都不是字母，就将上一行复制下来，也一定能组成矩形。
### 贪心证明
若一行内有字母，则一定能将其分为不同字母组成的矩形，办法可为：每个字母将左侧空位置转化为自身，最后一个字母要把右边所有空位置转化为自身。
![](https://cdn.luogu.com.cn/upload/image_hosting/shgfput8.png)
若一行内没有字母，则将上一行复制下来，一定能让其分为不同字母组成跨多行矩形。
![](https://cdn.luogu.com.cn/upload/image_hosting/lvnm8zjz.png)
# 代码
注意：最后要将整个图从上到下扫一遍，避免一行没有字母，上一行也没有字母的情况。（会在第一行无字母且第二行也无字母时出现）
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,r,c;
char a[50][50];
void fenpei(int x){
    char f[26],cnt=0,num=1;
    for(int i=1;i<=c;i++){
        if(a[x][i]!='?'){
            f[++cnt]=a[x][i];//将所有字母存下来
        }
    }
    if(cnt==0){
        for(int i=1;i<=c;i++)
            a[x][i]=a[x-1][i];//若一行内没有字母，则将上一行复制下来
    }
    else{
        for(int i=1;i<=c;i++){
            if(a[x][i]=='?'||a[x][i]==f[num]){//若无字母或是本身
                a[x][i]=f[num];//转化
            }
            else
                num++;//切换为下一个字母
            }
    }
}
int main(){
    cin>>t;
    for(int k=1;k<=t;k++){
        memset(a,0,sizeof(char));
        cin>>r>>c;
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                cin>>a[i][j];//输入
        for(int i=1;i<=r;i++)
            fenpei(i);
        for(int i=r;i>=1;i--){
            for(int j=1;j<=c;j++){
                if(a[i][j]>'Z'||a[i][j]<'A')
                    a[i][j]=a[i+1][j];//将整个图从上到下扫一遍
            }
        }
        cout<<"Case #"<<k<<":"<<endl;
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                if(a[i][j]<='Z'&&a[i][j]>='A')
                cout<<a[i][j];//输出
            }
            cout<<endl;
        }
    }
return 0;
}
```

---

## 作者：_Hzq_ (赞：1)

# 题解：P13162 \[GCJ 2017 #1A] Alphabet Cake

### 题意

给一个 $r\times c$ 的矩阵，有一些点为空白点，问如何填这些空白点（不能填未出现过的字母）使得矩阵中相同字母组成的形状都为矩形。

### 方法

我们先考虑 $1$ 行 $c$ 列的矩阵，发现只需要依次将有字母的点向两侧的空白点填充即可。填充单行的代码如下。

```cpp line-numbers
for(j=0;j<c;j++)
{
  if(mapp[temp[i]][j]!='?')
  {
    k=j-1;
    while(k>=0&&mapp[temp[i]][k]=='?') mapp[temp[i]][k]=mapp[temp[i]][j],k--;
    k=j+1;
    while(k<c&&mapp[temp[i]][k]=='?') mapp[temp[i]][k]=mapp[temp[i]][j],k++;
  }
}
```

随后考虑完整的矩阵，我们只需将每个有字母的一行单独操作，再向上向下填充空白行即可。

### AC 代码

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
const int N=27;
string mapp[N];
int T,realT,r,c;
bool bz[N];
vector<int> temp;
int main()
{
	cin >> T;
	realT=T;
	int i,j,k;
	while(T--)
	{
		temp.clear();
		cin >> r >> c;
		for(i=1;i<=r;i++)
		{
			bz[i]=0;
			cin >> mapp[i];
			for(j=0;j<c;j++)
				if(mapp[i][j]!='?')
				{
					if(bz[i]==0) temp.push_back(i);
					bz[i]=1;
				}
		}
		for(i=0;i<temp.size();i++)
		{
			for(j=0;j<c;j++)
			{
				if(mapp[temp[i]][j]!='?')
				{
					k=j-1;
					while(k>=0&&mapp[temp[i]][k]=='?') mapp[temp[i]][k]=mapp[temp[i]][j],k--;
					k=j+1;
					while(k<c&&mapp[temp[i]][k]=='?') mapp[temp[i]][k]=mapp[temp[i]][j],k++;
				}
			}
			k=temp[i]-1;
			while(bz[k]==0&&k>=1)
			{
				bz[k]=1;
				mapp[k]=mapp[temp[i]];
				k--;
			}
			k=temp[i]+1;
			while(bz[k]==0&&k<=r)
			{
				bz[k]=1;
				mapp[k]=mapp[temp[i]];
				k++;
			}
		}	
		printf("Case #%d:\n",realT-T);
		for(i=1;i<=r;i++)
			cout << mapp[i] << endl;
	}
	return 0;
}
```

---

