import time
import random

'''

모: 2.29% 윷: 13.94% 걸: 35.49% 개: 33.89% 도: 10.79% 뒷도: 3.60%

낙 8.0%

'''

print('\n\n\nWelcome to 61st BRASS YutnolYEE\n\n\n')

input()

tm=['악!','ack!','惡!']

while True:
    print('윷을 던집니다')


    for i in range(len(tm)):
        print(tm[i])
        time.sleep(0.8)

    print('\n')
    num= random.random()
    if num<0.05:
        print('낙\n')

        input()

    else:
        numm = random.random()

        if numm<0.0229:
            print('모\n')
        elif numm<0.0229+0.1394:
            print('윷\n')
        elif numm<0.0229+0.1394+0.3549:
            print('걸\n')
        elif numm<0.0229+0.1394+0.3549+0.3389:
            print('개\n')
        elif numm<0.0229+0.1394+0.3549+0.3389+0.1079:
            print('도\n')
        else:
            print('백도\n')

        input()
