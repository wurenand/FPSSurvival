# 游戏公开课大作业
实现了**支持联网**的两种游戏模式：1.类吸血鬼幸存者模式 2.普通CS团队竞技模式

**演示视频地址：** https://www.bilibili.com/video/BV1A9N6eoEWB/?share_source=copy_web&vd_source=38644d178e20382fb7837c5ea447501c

# 基本系统组成

## 输入系统

- **APlayerController**：负责绑定输入Action，将输入**转发**给Pawn（需要实现下面的Interface）
- **IHandleInputInterface**：**Pawn需要实现**，从而能够定制Pawn面对同种输入的不同的相应功能

## 角色 Character

大部分核心逻辑在此。分别在PossessedBy（Server）和OnRep_PlayerState（Client）中负责初始化AbilityComponent，Weapon，HUD参数

开火换弹逻辑

## Ability系统

**参考GAS系统的思路，实现支持配表配置等级属性数值的功能，可以在游戏中根据当前的Ability情况，随机查表提供可升级选项。**

初始技能包括：Weapon（子弹，射速，伤害） Health（生命值，最大生命值）

- **UAbilityComponent**：位于PlayerState中，核心组件，负责记录Ability。并作为管理者，通知Ability升级，更新广播数值，并转发给外界。负责授予Ability，以及Ability的同步

- **UAbilityBase**:一个UObject，作为所有Ability的基类，保存自己Ability的CurveTable，数据由Base * Mult构成，实现通过配表按等级获取数据。提供接口给外部获取数值，并广播每项数据的计算结果

- **FAbilityHandle**：用来同步Ability所有的结构体，它包含AbilityName和Level，会被同步给Clients（因为AbilityBase是UObject默认不支持同步）用于Clients通过它来得知

- **FAbilityDataTableRow**:Ability表中的表项，一项代表一个Ability，是**查表的核心**。下面是核心成员

  AbilityName 标识Ability
  AbilityClass Ability对应的UAbilityBase的Class

  AbilityCurveTable 是Ability的各项属性的数值来源，每条曲线代表一个属性

- **UActiveAbilityBase**：非纯数据能力基类，使用一个Timer来定时触发主动逻辑


## UI系统

基于MVC框架实现了UI系统。由WidgetController，HUD，OverlayPage（Widget），组成

- **HUD**：作为管理Widget的核心类，负责初始化所有OverlayPage（Widget），创建并绑定WidgetController中的参数。可以根据PageName切换Page（**切换页面**）
- **WidgetController**：包含所需要获取数据的来源，如Character，PlayerState等。
- **SurvivalWidget**：所有Widget的基类。包含一个WidgetController成员，一个SetWidgetController函数，一个AfterWidgetControllerSet函数  以及一个AfterChooseThisPage函数。

**两个After开头的函数都是手动的回调函数**，第一个会在SetWidgetController末尾自动调用，用于蓝图中根据新的WidgetController来绑定Controller其中的信息源的变量。第二个是HUD负责切换页面后，负责设置鼠标指针，输入模式等的设置


## 对象池系统 ActorPool

为了解决子弹/敌人重复Spawn Destroy导致的性能问题。自制了一个对象池插件，支持使用DA配置。

- **ObjectPoolComponent**：核心组件，对象池拥有者挂载，根据ProfileDataAsset进行初始化对象池。提供获取（如果超额获取还能新Spawn并加入对象池），释放对象功能
- **ObjectPoolProfileDataAsset**：对象池组件的配置文件。包括PoolActor类，对象池最大容量，对象池初始对象数量。
- **PoolActor**：对象池对象基类。自定义了BeginPlay逻辑（多播），生命周期系统，销毁。包括：所在的PoolComponent，自己是否Enable（以及相关逻辑，如设定更新频率，设定是否Hidden，启用碰撞等）

## AI系统

实现了敌人ai，如果设定了巡逻路线，则按照巡逻路线巡逻，否则随机巡逻。发现敌人后会追逐敌人，追到后会攻击，在追击过程中丢失视野2s会放弃。

## SpawnEnemy系统

实现了配表按照时间段生成指定的Class和数量

- **SpawnProfileData**：数据表，包含时间段长度，等级，和一个ClassToCount的Map
- **SpawnComponent**：核心组件，根据指定的Profile来按照区间SpawnClass。提供外部接口:开始，停止
