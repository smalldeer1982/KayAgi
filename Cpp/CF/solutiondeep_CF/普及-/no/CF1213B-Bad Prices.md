# 题目信息

# Bad Prices

## 题目描述

Polycarp analyzes the prices of the new berPhone. At his disposal are the prices for $ n $ last days: $ a_1, a_2, \dots, a_n $ , where $ a_i $ is the price of berPhone on the day $ i $ .

Polycarp considers the price on the day $ i $ to be bad if later (that is, a day with a greater number) berPhone was sold at a lower price. For example, if $ n=6 $ and $ a=[3, 9, 4, 6, 7, 5] $ , then the number of days with a bad price is $ 3 $ — these are days $ 2 $ ( $ a_2=9 $ ), $ 4 $ ( $ a_4=6 $ ) and $ 5 $ ( $ a_5=7 $ ).

Print the number of days with a bad price.

You have to answer $ t $ independent data sets.

## 样例 #1

### 输入

```
5
6
3 9 4 6 7 5
1
1000000
2
2 1
10
31 41 59 26 53 58 97 93 23 84
7
3 2 1 2 3 4 5
```

### 输出

```
3
0
1
8
2
```

# AI分析结果

### 题目内容
# 糟糕的价格

## 题目描述
Polycarp分析新款berPhone的价格。他掌握了过去n天的价格：$a_1, a_2, \dots, a_n$，其中$a_i$是第$i$天berPhone的价格。

Polycarp认为，如果之后（即天数编号更大的某一天）berPhone以更低的价格出售，那么第$i$天的价格就是糟糕的。例如，如果$n = 6$且$a = [3, 9, 4, 6, 7, 5]$，那么价格糟糕的天数为$3$天，即第$2$天（$a_2 = 9$）、第$4$天（$a_4 = 6$）和第$5$天（$a_5 = 7$）。

请输出价格糟糕的天数。

你需要回答$t$组独立的数据集。

## 样例 #1
### 输入
```
5
6
3 9 4 6 7 5
1
1000000
2
2 1
10
31 41 59 26 53 58 97 93 23 84
7
3 2 1 2 3 4 5
```
### 输出
```
3
0
1
8
2
```
• **算法分类**：模拟
• **综合分析与结论**：这些题解核心思路相近，均基于题目定义判断糟糕价格天数。多数题解选择倒序遍历数组，维护最小值，当当前价格大于最小值时，糟糕价格天数加一。部分题解使用优先队列、栈等数据结构辅助判断。不同题解在代码实现细节、输入输出方式、变量命名和代码风格上存在差异。
• **所选的题解**
  - **作者：cqbztz2（5星）**
    - **关键亮点**：思路清晰，先分析时间复杂度，确定算法需满足$O(Tn)$，随后明确倒序遍历找最小值的核心思路，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[150005],ans,minn;
signed main(){
    cin>>T;
    while(T--){
        minn=INT_MAX,ans=0;
        cin>>n;
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int i=n;i>=1;--i){
            if(a[i]>minn) ++ans;
            else minn=a[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：外层循环处理$T$组数据，每次读入$n$及$n$个价格，内层倒序遍历数组，通过比较当前价格与最小值更新糟糕价格天数及最小值。
  - **作者：andyli（4星）**
    - **关键亮点**：提出类似滑动窗口思路，利用优先队列辅助判断，从另一个角度解决问题。
    - **重点代码**：
```cpp
#include <cstdio>
#include <queue>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        priority_queue<int> q;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            while (!q.empty() && x < q.top())
                q.pop(), ans++;
            q.push(x);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
核心实现思想：每次读入一个价格，将优先队列中比该价格大的元素弹出并统计次数，最后输出糟糕价格天数。
  - **作者：pandaSTT（4星）**
    - **关键亮点**：先分析$O(n^2)$暴力算法会超时，进而优化为倒序枚举更新最小值的$O(n)$算法，思路完整，还给出卡最优解的输入输出优化。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline char gc(){
    static char buf[1000010],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    register int x=0,f=0;
    static char s=gc();
    while(s<'0'||s>'9')f|=s=='-',s=gc();
    while(s>='0'&&s<='9'){
        x=(x<<3)+(x<<1)+(s^48);s=gc();
    }return f?-x:x;
}
inline void write(register int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);putchar(x%10^48);
}//卡最优解用的
const int N=150005;
int t,n,a[N],ans,minn;
signed main(){
    t=read();
    while(t--){
        minn=0x3f3f3f3f;
        ans=0;
        n=read();
        for(int i=1;i<=n;a[i++]=read());
        for(int i=n;i>=1;i--){//倒着更新最小值
            if(a[i]>minn){
                ans++;
            }
            else{
                minn=a[i];
            }
        }
        write(ans);
        putchar('\n');
    }
    return 0;
}
```
核心实现思想：通过自定义高效输入输出函数优化，主体部分与其他倒序遍历题解类似，倒序遍历数组判断并更新糟糕价格天数和最小值。
• **最优关键思路或技巧**：倒序遍历数组并维护最小值，可高效判断每一天价格是否糟糕。这种思路避免了对每个价格都进行后续所有价格的比较，降低时间复杂度。
• **同类型题或类似算法套路**：此类题目核心是对序列元素按特定规则进行判断计数。类似套路是根据题目条件，选择正序或倒序遍历，维护关键变量（如最值、和等）辅助判断。
• **推荐题目**：
  - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
  - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
  - [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)
• **个人心得**：无

---
处理用时：56.67秒