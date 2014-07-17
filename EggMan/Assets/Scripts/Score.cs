using UnityEngine;
using System.Collections;

public class Score : MonoBehaviour {

	public GUIText scoreGUIText;
	private int score;

	void Start ()
	{
		Initialize ();
	}
	
	void Update ()
	{
		scoreGUIText.text = score.ToString ();
	}
	
	// ゲーム開始前の状態に戻す
	private void Initialize ()
	{
		score = 0;
	}
	
	// ポイントの追加
	public void AddPoint (int point)
	{
		score = score + point;
		if(score < 0){
			score = 0;
		}
	}

}
