# Treasure_Hunt

보물찾기 게임

C언어 팀 프로젝트로 진행한 보물찾기 게임 소스코드입니다.
주어진 크기의 맵 안에서 장애물을 피해 보물이 숨겨진 깃발을 찾으면 승리하는 게임으로, 초급/중급/고급의 3단계로 이루어져 있습니다.
2차원 배열을 이용하여 맵을 표현하였고, 플레이어, 블럭(장애물), 깃발(버프/디버프/보물), 건덕이(부딪히면 죽는 장애물) 등의 오브젝트가 존재합니다.
스토리와 인트로, 메뉴 화면, 순위 등 추가 기능들도 구현하였습니다.

<주요 기능 설명>
- 스토리와 인트로
![image](https://user-images.githubusercontent.com/105623744/212006596-c3914ca7-ca24-4b11-a66a-a09f445105df.png)
![image](https://user-images.githubusercontent.com/105623744/212006628-0b242743-b146-461a-9bd4-d47d192a5f57.png)
게임의 컨셉은 건국대학교 22학번 새내기가 보물을 찾으러 일감호를 탐험하는 내용입니다. 게임 시작 시 한 글자씩 스토리를 출력한 뒤, "일감호 아래 보물을 찾아라!" 라는 제목이 출력된 메인 화면이 등장합니다.
 
- 메뉴
메뉴는 아래와 같이 구성되며, 방향키를 이용해 옆에 있는 화살표를 위아래로 움직여 메뉴를 선택할 수 있습니다.
![image](https://user-images.githubusercontent.com/105623744/212007297-bb0861f1-db5b-4a2d-b2b5-bd372fd65d84.png)

- 게임 시작 메뉴
게임 시작을 선택하면 초급, 중급, 고급 중 하나의 단계를 선택할 수 있습니다. 각 단계가 끝나면 고급 단계를 완료할 때까지 다음 단계로 계속해서 넘어갑니다.

게임 초기화
난이도별로 아래와 같은 설정 값을 적용하여 맵을 생성합니다.
	                  초급	중급	고급
맵의 크기	         30*30	40*40	50*50
블록 개수	           10	   10	   10
깃발 개수(보물 개수) 6(1)	 6(1)	 6(1)
건덕이 개수        	 1	   2   	 3
제한 시간          	60초	 60초	 60초

게임을 시작하면 아래와 같은 화면을 띄워 줍니다.
![image](https://user-images.githubusercontent.com/105623744/212009035-cb296a42-2f46-481a-9477-5582aa871147.png)

왼쪽 위에 있는 마름모(플레이어)를 방향키를 이용해 조작하여 보물이 있는 깃발을 찾으면 승리합니다.
깃발의 종류는 다음과 같습니다.
- 보물
찾으면 게임에서 승리하는 깃발로, 한 게임에 오직 하나만 존재합니다.
- 버프
보호막 : 다음에 디버프 깃발을 만났을 때 그 효과를 방어하는 역할을 합니다.
시간 추가 : 제한 시간을 15초 늘려줍니다.
- 디버프
방향키 반전 : 5초 동안 위아래, 왼쪽 방향키를 반전시키는 역할을 합니다.
속박 : 플레이어를 5초 동안 움직이지 못하게 합니다.
시간 감소 : 제한 시간을 15초 줄입니다.
시작 위치로 : 플레이어를 처음 시작 위치로 돌려 보냅니다.

또한, 별 모양으로 표시된 건덕이는 마주치면 게임에서 패배합니다.

제한 시간 내에 보물 깃발을 찾으면 'MISSION COMPLETE'라는 문구가 5번 깜박인 뒤 닉네임 입력 창으로 넘어갑니다.
닉네임을 입력하면 현재 난이도와 플레이 시간이 출력되고, 다음 단계로 넘어갈지 선택할 수 있다. ‘예’를 선택하면 다음 단계로 넘어가고, ‘아니오’를 선택하면 메뉴 화면으로 돌아간다.
![image](https://user-images.githubusercontent.com/105623744/212010720-035f8806-05c1-4956-81af-3bd00e872e45.png)
