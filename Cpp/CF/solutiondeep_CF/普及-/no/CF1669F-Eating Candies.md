# 题目信息

# Eating Candies

## 题目描述

There are $ n $ candies put from left to right on a table. The candies are numbered from left to right. The $ i $ -th candy has weight $ w_i $ . Alice and Bob eat candies.

Alice can eat any number of candies from the left (she can't skip candies, she eats them in a row).

Bob can eat any number of candies from the right (he can't skip candies, he eats them in a row).

Of course, if Alice ate a candy, Bob can't eat it (and vice versa).

They want to be fair. Their goal is to eat the same total weight of candies. What is the most number of candies they can eat in total?

## 说明/提示

For the first test case, Alice will eat one candy from the left and Bob will eat one candy from the right. There is no better way for them to eat the same total amount of weight. The answer is $ 2 $ because they eat two candies in total.

For the second test case, Alice will eat the first three candies from the left (with total weight $ 7 $ ) and Bob will eat the first three candies from the right (with total weight $ 7 $ ). They cannot eat more candies since all the candies have been eaten, so the answer is $ 6 $ (because they eat six candies in total).

For the third test case, there is no way Alice and Bob will eat the same non-zero weight so the answer is $ 0 $ .

For the fourth test case, Alice will eat candies with weights $ [7, 3, 20] $ and Bob will eat candies with weights $ [10, 8, 11, 1] $ , they each eat $ 30 $ weight. There is no better partition so the answer is $ 7 $ .

## 样例 #1

### 输入

```
4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10```

### 输出

```
2
6
0
7```

# AI分析结果

### 题目内容
# 吃糖果

## 题目描述
有\(n\)颗糖果从左到右放在桌子上。糖果从左到右编号。第\(i\)颗糖果的重量为\(w_i\)。爱丽丝（Alice）和鲍勃（Bob）吃糖果。
爱丽丝可以从左边吃任意数量的糖果（她不能跳过糖果，必须连续吃）。
鲍勃可以从右边吃任意数量的糖果（他不能跳过糖果，必须连续吃）。
当然，如果爱丽丝吃了一颗糖果，鲍勃就不能吃它（反之亦然）。
他们希望公平分配。他们的目标是吃到相同总重量的糖果。他们总共最多能吃多少颗糖果？

## 说明/提示
对于第一个测试用例，爱丽丝从左边吃一颗糖果，鲍勃从右边吃一颗糖果。对他们来说，没有更好的方法能吃到相同的总重量。答案是\(2\)，因为他们总共吃了两颗糖果。
对于第二个测试用例，爱丽丝从左边吃前三颗糖果（总重量为\(7\)），鲍勃从右边吃前三颗糖果（总重量为\(7\)）。他们不能再吃更多糖果了，因为所有糖果都已被吃掉，所以答案是\(6\)（因为他们总共吃了六颗糖果）。
对于第三个测试用例，没有办法让爱丽丝和鲍勃吃到相同的非零重量，所以答案是\(0\)。
对于第四个测试用例，爱丽丝吃重量为\([7, 3, 20]\)的糖果，鲍勃吃重量为\([10, 8, 11, 1]\)的糖果，他们每人都吃了\(30\)重量的糖果。没有更好的分配方式，所以答案是\(7\)。

## 样例 #1
### 输入
```
4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10
```
### 输出
```
2
6
0
7
```

### 算法分类
双指针（属于双指针算法下的一种应用场景，本质上也可归为枚举优化，这里选双指针更能体现解题核心思路）

### 题解综合分析与结论
- **思路对比**：
    - **IvanZhang2009**：使用双指针，一个指针从前往后遍历表示Alice吃的糖果，另一个指针从后往前遍历表示Bob吃的糖果，每次移动前指针后，调整后指针使Bob吃的糖果重量大于等于Alice吃的，若相等则更新答案。
    - **GI录像机**：先计算前缀和并存储在map中，再通过后缀和在map中查找相等的前缀和，同时要判断两人吃的糖果无交集，时间复杂度从\(O(n^2)\)优化到\(O(nlogn)\)。
    - **happy_dengziyue**：先计算前缀和与后缀和，枚举Alice吃的糖果范围，通过二分查找后缀和中与之相等的部分，从而确定Bob吃的糖果范围。
    - **charleshe**：用deque模拟，每次根据Alice和Bob已吃糖果的总质量比较结果，决定给Alice或Bob分配糖果，最后队列空时再判断一次两人糖果质量是否相等。
- **算法要点对比**：
    - **IvanZhang2009**：双指针移动过程中，通过不断调整指针位置来寻找重量相等的情况，核心在于指针移动和重量比较。
    - **GI录像机**：利用map存储前缀和优化查找，重点在于前缀和计算、map使用以及交集判断。
    - **happy_dengziyue**：通过二分查找优化暴力枚举后缀和的过程，关键是前缀和、后缀和计算以及二分查找实现。
    - **charleshe**：利用deque模拟取糖果过程，依据两人已吃糖果重量动态分配糖果，最后需额外判断队列空时的情况。
- **解决难点对比**：
    - **IvanZhang2009**：难点在于双指针移动逻辑设计，如何在移动过程中准确找到重量相等的情况。
    - **GI录像机**：优化暴力枚举的复杂度，利用map存储和查找前缀和，同时正确判断交集是关键。
    - **happy_dengziyue**：二分查找后缀和中与前缀和相等的位置，需正确实现二分查找逻辑。
    - **charleshe**：合理利用deque模拟取糖果过程，避免因deque常数大导致TLE，同时注意最后队列空时的特殊判断。

### 所选的题解
- **IvanZhang2009（5星）**
    - **关键亮点**：双指针思路清晰，代码简洁高效，直接利用双指针移动和重量比较来求解，时间复杂度为\(O(n)\)。
    - **重点代码**：
```cpp
void Main(){
    cin>>n;
    REP(i,0,n)cin>>a[i];
    int x=0,y=n-1;
    int sum1=0,sum2=0,ans=0;
    while(x<=y){
        sum1+=a[x];
        while(y>x&&sum2<sum1)sum2+=a[y],y--;
        if(sum2==sum1)ans=max(ans,x+n-y);
        x++;
    }
    cout<<ans<<endl;
}
```
    - **核心实现思想**：初始化双指针\(x\)、\(y\)分别指向数组两端，用\(sum1\)、\(sum2\)记录两人吃的糖果重量，在双指针未相遇时，移动前指针\(x\)并更新\(sum1\)，同时移动后指针\(y\)使\(sum2\geq sum1\)，若\(sum2 == sum1\)，则更新两人最多吃的糖果总数。
- **happy_dengziyue（4星）**
    - **关键亮点**：利用前缀和、后缀和以及二分查找，思路清晰，将暴力枚举的时间复杂度优化。
    - **重点代码**：
```cpp
int ask(int l,int r,int x){
    int mid;
    int res=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(x==sr[mid]){
            res=mid;
            break;
        }
        if(x<sr[mid])l=mid+1;
        else r=mid-1;
    }
    return res;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",a+i);
        sl[0]=0;
        for(int i=1;i<=n;++i)sl[i]=sl[i-1]+a[i];
        sr[n+1]=0;
        for(int i=n;i>=1;--i)sr[i]=sr[i+1]+a[i];
        ans=0;
        for(int i=1,x;i<=n;++i){
            x=ask(i+1,n,sl[i]);
            if(x!=-1)ans=max(ans,i+n-x+1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：先计算前缀和数组\(sl\)与后缀和数组\(sr\)，通过二分查找函数\(ask\)在后缀和数组中查找与当前前缀和相等的位置，若找到则更新两人最多吃的糖果总数。
- **GI录像机（4星）**
    - **关键亮点**：利用map优化查找前缀和的过程，巧妙利用数据范围特点优化暴力枚举，时间复杂度为\(O(nlogn)\)。
    - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    a[i] = read();
    hsum[i] = hsum[i - 1] + a[i];
    mp[hsum[i]] = i;
}
for (int i = n; i >= 1; i--) {
    tsum[i] = tsum[i + 1] + a[i];
    if (mp[tsum[i]] && i > mp[tsum[i]])ans = max(ans, n - i + 1 + mp[tsum[i]]);
}
```
    - **核心实现思想**：先计算前缀和数组\(hsum\)并将其值与下标存入map容器\(mp\)，再计算后缀和数组\(tsum\)，在后缀和计算过程中，若map中存在与之相等的前缀和且满足两人吃的糖果无交集，则更新两人最多吃的糖果总数。

### 最优关键思路或技巧
双指针法是较优的思路，通过两个指针分别从两端移动，动态调整两人吃的糖果范围，在\(O(n)\)时间复杂度内高效解决问题。这种方法避免了如暴力枚举或使用map等带来的额外时间或空间开销，代码实现简洁直观。

### 可拓展之处
同类型题通常围绕数组或序列的两端操作，通过双指针、前缀和等方法优化枚举过程。类似算法套路如在处理有序数组的一些问题时，双指针可用于查找满足特定条件的元素对。例如在两数之和等于目标值的问题中，可利用双指针从数组两端相向移动查找。

### 洛谷题目推荐
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：同样涉及双指针思想，通过移动指针寻找满足条件的子序列。
- [P2678 [NOIP2015 普及组] 跳石头](https://www.luogu.com.cn/problem/P2678)：利用二分查找解决类似在序列中寻找满足特定条件的最大/最小值问题，与本题通过二分查找后缀和思路类似。
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：可通过排序后利用双指针优化暴力枚举，与本题优化查找过程思路类似。 

---
处理用时：64.74秒