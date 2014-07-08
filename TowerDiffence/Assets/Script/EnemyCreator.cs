using UnityEngine;
using System.Collections;

public class EnemyCreator : MonoBehaviour {
	public GameObject enemy;
	public float seconds = 5f;

	// Startメソッドをコルーチンとして呼び出す
	IEnumerator Start ()
	{
		while (true) {

			int rand = Random.Range(1, 5);
			
			switch(rand){
			case 1:
				transform.position = new Vector2 (6, Random.Range (-4f, 5f));
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			case 2:
				transform.position = new Vector2 (-6, Random.Range (-4f, 5f));
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			case 3:
				transform.position = new Vector2 (Random.Range (-6f, 7f), 4);
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			case 4:
				transform.position = new Vector2 (Random.Range (-6f, 7f), -4);
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			default:
				break;
			}
			// seconds秒待つ
			yield return new WaitForSeconds (seconds);

		}
	}
	
	// Update is called once per frame
	void Update () {

	}
}
