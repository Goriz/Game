using UnityEngine;
using System.Collections;

public class MakeEggMan : MonoBehaviour {


	public GameObject eggman;
	// Use this for initialization
	IEnumerator Start ()
	{
		while (true) {

			//float rnd_chara = Random.value * 8;
			//Debug.Log(rnd_chara);
			//Debug.Log(Mathf.FloorToInt(rnd_chara));

			float place_vector = Random.value * 3;
			float place_direction = Random.value;
			if(place_direction >=  0.5){
				place_vector = place_vector * -1;
			}
			Vector2 appearPoint = new Vector2(place_vector,6);

			// 弾をプレイヤーと同じ位置/角度で作成
			Instantiate (eggman, appearPoint, transform.rotation);
			// 0.05秒待つ
			yield return new WaitForSeconds (0.5f);
		}
	}
	// Update is called once per frame
	void Update () {
	
	}
}
