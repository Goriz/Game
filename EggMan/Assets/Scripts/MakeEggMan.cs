using UnityEngine;
using System.Collections;

public class MakeEggMan : MonoBehaviour {


	public GameObject eggman;
	public GameObject eggman2;
	public GameObject eggman3;
	public GameObject eggman4;
	public GameObject eggman5;
	public GameObject eggman6;
	public GameObject eggman7;
	public GameObject eggman8;
	// Use this for initialization
	IEnumerator Start ()
	{	
		GameObject test = null;
		int i;
		while (true) {

			//float rnd_chara = Random.value * 8;
			//Debug.Log(rnd_chara);
			//Debug.Log(Mathf.FloorToInt(rnd_chara));
			//GameObject eggman = GameObject.Find("EggMan");
			float rndEgg = Random.value * 8;
			i = Mathf.FloorToInt(rndEgg);
			//test = eggman;
			switch(i){
				case 0 : test = eggman;
					break;
				case 1 : test = eggman2;
					break;
				case 2 : test = eggman3;
					break;
				case 3 : test = eggman4;
					break;
				case 4 : test = eggman5;
					break;
				case 5 : test = eggman6;
					break;
				case 6 : test = eggman7;
					break;
				case 7 : test = eggman8;
					break;
			}
				

			float place_vector = Random.value * 3;
			float place_direction = Random.value;
			if(place_direction >=  0.5){
				place_vector = place_vector * -1;
			}
			Vector2 appearPoint = new Vector2(place_vector,6);

			// 弾をプレイヤーと同じ位置/角度で作成
			Instantiate (test, appearPoint, transform.rotation);
			//Instantiate (test, appearPoint, transform.rotation);
			// 0.05秒待つ
			yield return new WaitForSeconds (0.5f);
			Debug.Log(i);
		}
	}
	// Update is called once per frame
	void Update () {
	
	}
}
