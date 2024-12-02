# Simulazione del Decadimento della Particella K\*⁰

**Autori**: Malagoli Tommaso Andrea, Mazzi Davide, Pivi Riccardo, Schirripa Mattia  
**Data**: Novembre 2024  

## Introduzione

Questo progetto simula eventi fisici risultanti da collisioni di particelle elementari.  
Il codice, scritto in C++, utilizza la libreria ROOT per analisi dati e generazione di grafici.  

## Struttura del Codice

Il programma implementa tre classi principali:  

1. **ParticleType**  
   - Descrive massa, carica e nome delle particelle elementari.  

2. **ResonanceType**  
   - Estende `ParticleType` includendo la larghezza di risonanza.  

3. **Particle**  
   - Descrive quantità di moto e include un array di puntatori a `ParticleType`.  

### Gerarchia delle Classi

- `ResonanceType` eredita da `ParticleType` e sovrascrive il metodo `Print()`.  
- `Particle` utilizza una relazione *has-a* con `ParticleType`.  

### Principali Funzioni Implementate

- `FindParticle()`: Trova l'indice di una particella.  
- `TotalEnergy()`: Calcola l'energia totale secondo la relatività.  
- `InvMass()`: Calcola la massa invariante.  
- `Decay2body()`: Simula il decadimento a due corpi per particelle K\*⁰.  

## Generazione degli Eventi

- Generati \(10^5\) eventi totali.  
- Ogni evento contiene almeno 100 particelle, con una protezione `size-safe` per evitare `segmentation fault`.  
- Distribuzione delle particelle secondo le probabilità specificate:  

| Particella | Probabilità (%) |
|------------|-----------------|
| π⁺         | 40             |
| π⁻         | 40             |
| k⁺         | 5              |
| k⁻         | 5              |
| p⁺         | 4.5            |
| p⁻         | 4.5            |
| K\*⁰       | 1              |

Le particelle sono generate stocasticamente utilizzando il metodo Monte Carlo di ROOT.

## Analisi dei Dati

I dati sono analizzati tramite istogrammi che mostrano:  

- Distribuzione dell'angolo polare e azimutale.  
- Modulo dell'impulso.  
- Masse invarianti.  

### Confronto tra Occorrenze Osservate e Attese

| Particella | Occorrenze Osservate | Occorrenze Attese |
|------------|-----------------------|-------------------|
| π⁺         | 4 × 10⁶              | 4 × 10⁶          |
| π⁻         | 4 × 10⁶              | 4 × 10⁶          |
| k⁺         | 0.5 × 10⁶            | 0.5 × 10⁶        |
| k⁻         | 0.5 × 10⁶            | 0.5 × 10⁶        |
| p⁺         | 0.45 × 10⁶           | 0.45 × 10⁶       |
| p⁻         | 0.45 × 10⁶           | 0.45 × 10⁶       |
| K\*⁰       | 0.1 × 10⁶            | 0.1 × 10⁶        |

## Risultati dei Fit

Distribuzioni principali e parametri dei fit:  

1. **Angolo Polare e Azimutale**: Distribuzione uniforme.  
2. **Modulo dell'Impulso**: Fit esponenziale.  
3. **Massa Invariante di K\*⁰**: Fit gaussiano con parametri osservati.  

## Come Eseguire il Progetto

1. Clona questo repository.  
2. Assicurati che il file `compile.sh` abbia i permessi di esecuzione:
   ```bash
   chmod +x compile.sh


/*This is a try
in Particle.hpp l'array P permette di usare gli algoritmi
NON usare std::vector nel vettore grande*/
