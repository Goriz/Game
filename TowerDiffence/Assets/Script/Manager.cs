using UnityEngine;
using System.Collections;

public class Manager : MonoBehaviour {
	// Playerプレハブ
	public GameObject player;
	
	// タイトル
	private GameObject title;
	
	void Start ()
	{

	}
	
	void Update ()
	{

	}
	
	void GameStart ()
	{
		// ゲームスタート時に、タイトルを非表示にしてプレイヤーを作成する
		title.SetActive (false);
		Instantiate (player, player.transform.position, player.transform.rotation);
	}
	
	public void GameOver ()
	{
		// ゲームオーバー時に、タイトルを表示する
		title.SetActive (true);
	}
	
	public bool IsPlaying ()
	{
		// ゲーム中かどうかはタイトルの表示/非表示で判断する
		return title.activeSelf == false;
	}	
}
