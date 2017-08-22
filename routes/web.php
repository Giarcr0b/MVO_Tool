<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| This file is where you may define all of the routes that are handled
| by your application. Just tell Laravel the URIs it should respond
| to using a Closure or controller method. Build something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', 'HomeController@index');

// Route::post('/portfolios', 'PortfoliosController@store');

/**
 *  Resourceful route for Portfolios
 *
 */
Route::resource('portfolios', 'PortfolioController');

/**
 * Resourceful route for Stocks
 */

Route::post('findstocks/{id}', ['uses' => 'StockController@find']);
Route::get('buildfrontier/{id}/{markets}', ['uses' => 'StockController@build']);
Route::resource('stocks', 'StockController');



/**
 * Resourceful route for OPtimisations
 */
Route::post('make', ['uses' => 'OptimisationController@make']);
Route::resource('optimisations', 'OptimisationController');