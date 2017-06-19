#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <random>
#include <string>
#include <ctime>

using namespace std;

unsigned long
hashFunction (unsigned long h, const char *str)
{
  int c;
  while (c = *str++)
    h = ((h << 5) + h) + c;
  return h;
}

vector < string > candidatos;

int
main ()
{
  clock_t begin = clock ();
  int n;
  cout << "Numero de archivos a comparar: ";
  cin >> n;
  int k, nHash, nShingles;
  cout << "Introduce valor de k: ";
  cin >> k;
  cout << "Introduce porcentaje de shingles a computar: ";
  int percent;
  cin >> percent;
  cout << "Introduce numero de funciones de hash: ";
  cin >> nHash;

  vector < vector < int >>hashValues (nHash, vector < int >(2, 0));
  random_device rd;
  for (int i = 0; i < nHash; ++i)
    {
      hashValues[i][0] = rd () % 100;
      hashValues[i][1] = rd () % 1000;
    }

  vector < vector < unsigned int >>mat;

  cout << "Nombres archivos a comparar: ";
  string file1;
  unordered_set < int >randomHashCodes;
  for (int l = 0; l < nHash; ++l)
    {
      bool ready = false;
      while (not ready)
	{
	  int randomN = rd () % 1000;
	  if (randomHashCodes.find (randomN) == randomHashCodes.end ())
	    {
	      randomHashCodes.insert (randomN);
	      ready = true;
	    }
	}
    }

  for (int i = 0; i < n; ++i)
    {
      cin >> file1;
      candidatos.push_back (file1);
      ifstream stream1 (file1.c_str ());
      unordered_set < string > set1;
      char c;
      if (stream1.is_open ())
	{
	  int numchars = 0;
	  string kshingle = "";
	  while (stream1.get (c))
	    {
	      if (numchars <= k)
		{
		  numchars++;
		  kshingle += c;
		}
	      else
		{
		  set1.insert (kshingle);
		  kshingle = kshingle.substr (1, k - 1) + c;
		}
	    }
	}
      else
	{
	  cout << "unable to open file " + file1 << endl;
	  exit (1);
	}
      if (i == 0)
	{
	  nShingles = (double) (set1.size () * percent) / (double) 100;
	  cout << "nShingles=" << nShingles << endl;
	}
      unordered_set < string > s1;
      unordered_set < string >::iterator it;
      it = set1.begin ();
      while (s1.size () < nShingles)
	{
	  int randomN = rd () % 5;
	  for (int l = 0; l < randomN; ++l)
	    {
	      ++it;
	      if (it == set1.end ())
		it = set1.begin ();
	    }
	  s1.insert (*it);
	}

      vector < unsigned int >sig1 (nHash, 0);
      unsigned long min1 = 0;


      unordered_set < int >::iterator it3 = randomHashCodes.begin ();
      for (int l = 0; l < nHash; ++l)
	{
	  it = s1.begin ();
	  int h = *it3;
	  ++it3;
	  for (int j = 0; j < nShingles; ++j)
	    {
	      string str1 = *it;
	      if (it == s1.begin ())
		min1 =
		  (hashValues[l][0] * hashFunction (h, str1.c_str ()) +
		   hashValues[l][1]) % nShingles;
	      else
		{
		  unsigned long x =
		    (hashValues[l][0] * hashFunction (h, str1.c_str ()) +
		     hashValues[l][1]) % nShingles;
		  if (x < min1)
		    min1 = x;
		}
	      ++it;
	    }
	  sig1[l] = min1;
	}
      mat.push_back (sig1);
    }

  cout << "Introduce el tamaño de las bandas: ";
  int bandas;
  cin >> bandas;
  vector < vector < int >>lshMat;
  vector < int >bucket1;
  cout << endl;
  vector < vector < string > >matBand (n,
				       vector < string > (nHash / bandas,
							  "0"));
  vector < vector < int >>matSim (n, vector < int >(n, 0));
  for (int i = 0; i < n; ++i)
    {
      int tmp = 0;
      string str = "";
      for (int j = 0; j <= nHash; ++j)
	{
	  if (tmp < bandas)
	    {
	      ++tmp;
	      str += to_string (mat[i][j]);
	    }
	  else
	    {
	      matBand[i][j / bandas - 1] = str;
	      if (j < nHash)
		str = to_string (mat[i][j]);
	      tmp = 1;
	    }
	}
    }

  int hashperbandas = nHash / bandas;
  double threshold =
    pow (((double) 1 / (double) hashperbandas),
	 ((double) 1 / (double) bandas));
  cout << endl << "Threshold de no-similitud = " << threshold << endl;

  for (int i = 0; i < n; ++i)
    {
      for (int j = i + 1; j < n; ++j)
	{
	  for (int k = 0; k < hashperbandas; ++k)
	    {
	      matSim[i][j] += (matBand[i][k] != matBand[j][k]) ? 1 : 0;
	      if (matSim[i][j] > (threshold * hashperbandas))
		{
		  matSim[i][j] = -1;
		  break;
		}
	    }
	}
    }
  for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
	{
	  cout << matSim[i][j] << " ";
	}
      cout << endl;
    }
  for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
	{
	  if (matSim[i][j] > 0)
	    cout << "Candidatos para comparacion: " << candidatos[i] << " y "
	      << candidatos[j] << endl;
	}
    }
  clock_t end = clock ();
  double elapsed_secs = double (end - begin) / (CLOCKS_PER_SEC / 1000);
  cout << "Timepo empleado: " << elapsed_secs << " ms" << endl;
}
